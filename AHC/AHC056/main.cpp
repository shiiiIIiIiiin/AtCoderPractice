#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <map>
#include <set>
#include <iterator>
#include <unordered_map>
#include <stack>
#include <string>
#include <cmath>
#include <iomanip>
#include <deque>
#include <unordered_set>
#include <locale>
#include <random>
#include <tuple> 

using namespace std;


// (dr, dc, dir_char, can_move, reconstruct_path, runBFS は変更なし)
int dr[] = { -1, 1, 0, 0, 0 }; // U, D, L, R, S
int dc[] = { 0, 0, -1, 1, 0 };
char dir_char[] = { 'U', 'D', 'L', 'R', 'S' };
bool can_move(int r, int c, int dir, int N, const std::vector<std::string>& v, const std::vector<std::string>& h) {
    if (dir == 0) return r > 0 && h[r - 1][c] == '0';
    if (dir == 1) return r < N - 1 && h[r][c] == '0';
    if (dir == 2) return c > 0 && v[r][c - 1] == '0';
    if (dir == 3) return c < N - 1 && v[r][c] == '0';
    return false;
}
vector<pair<int, int>> reconstruct_path(
    const map<pair<int, int>, pair<int, int>>& parent,
    pair<int, int> start, pair<int, int> end
) {
    vector<pair<int, int>> path;
    pair<int, int> curr = end;
    while (curr.first != -1) {
        path.push_back(curr);
        if (curr == start) break;
        if (parent.find(curr) == parent.end()) break;
        curr = parent.at(curr);
    }
    reverse(path.begin(), path.end());
    return path;
}
pair<int, map<pair<int, int>, pair<int, int>>> runBFS(
    int N, pair<int, int> start, pair<int, int> end,
    const vector<string>& v, const vector<string>& h
) {
    queue<pair<int, int>> q;
    q.push(start);
    map<pair<int, int>, pair<int, int>> parent;
    vector<vector<int>> dist(N, vector<int>(N, -1));
    dist[start.first][start.second] = 0;
    parent[start] = { -1, -1 };
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        if (r == end.first && c == end.second) break;
        for (int dir = 0; dir < 4; dir++) {
            if (can_move(r, c, dir, N, v, h)) {
                int nr = r + dr[dir];
                int nc = c + dc[dir];
                if (dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    parent[{nr, nc}] = { r, c };
                    q.push({ nr, nc });
                }
            }
        }
    }
    return { dist[end.first][end.second], parent };
}

// --- 戦略出力用の構造体 ---
struct Rule { int c, q, A, S; char D; };
struct StrategyOutput {
    int C, Q, M;
    vector<vector<int>> board;
    vector<Rule> rules;
    map<pair<int, int>, Rule> rule_map;
    // (シミュレーション開始状態は run_simulation 側で t=0 から計算)
};

// --- 状態圧縮のためのグローバル変数 ---
vector<int> behavior_id_of_t; 
map<tuple<int, int, int>, int> memo_behavior_to_id; 
int next_behavior_id;
vector<int> D_map_global;
vector<int> t_next_visit_global;
int X_global; 
int t_last_stop_global; 
bool use_random_walk_global; 

// (get_behavior_id は変更なし)
int get_behavior_id(int t) {
    if (t > X_global) return 0; 
    if (behavior_id_of_t[t] != -1) return behavior_id_of_t[t]; 

    tuple<int, int, int> behavior;
    if (use_random_walk_global && t == X_global) {
        int D = 0; int b_id_next = 0; int b_id_next_visit = 0; 
        behavior = { D, b_id_next, b_id_next_visit };
    } else if (!use_random_walk_global && t == X_global) {
        int D = 4; int b_id_next = 0; int b_id_next_visit = 0; 
        behavior = { D, b_id_next, b_id_next_visit };
    } else {
        int b_id_next = get_behavior_id(t + 1);
        int next_t = t_next_visit_global[t];
        int b_id_next_visit;
        if (next_t == -1 || next_t > X_global) {
            b_id_next_visit = 0; 
        } else {
            b_id_next_visit = get_behavior_id(next_t);
        }
        int D = D_map_global[t]; 
        behavior = { D, b_id_next, b_id_next_visit };
    }
    auto it = memo_behavior_to_id.find(behavior);
    if (it != memo_behavior_to_id.end()) {
        return behavior_id_of_t[t] = it->second;
    }
    int new_b_id = next_behavior_id++;
    memo_behavior_to_id[behavior] = new_b_id;
    return behavior_id_of_t[t] = new_b_id;
}


/**
 * @brief 戦略 A または B を生成する
 */
StrategyOutput generate_strategy(
    bool use_random_walk, int N, long long int X, 
    const vector<pair<int, int>>& full_path,
    const vector<string>& v, const vector<string>& h,
    int K 
) {
    // --- 1. グローバル変数を初期化・設定 ---
    memo_behavior_to_id.clear();
    next_behavior_id = 0; 
    use_random_walk_global = use_random_walk;

    if (use_random_walk) {
        X_global = t_last_stop_global; 
    } else {
        X_global = X; 
    }
    behavior_id_of_t.assign(X_global + 2, -1); 

    // --- 2. Phase 1: 状態圧縮 ---
    get_behavior_id(0); 
    int b_id_0 = (behavior_id_of_t.empty() ? 0 : behavior_id_of_t[0]);
    int b_id_unused = 0; 
    int M = next_behavior_id; 

    // --- 3. Phase 2: 再マッピング & C, Q 計算 ---
    map<int, int> b_id_to_s_id; 
    map<int, int> s_id_to_b_id; 
    int current_s_id = 0; 
    b_id_to_s_id[b_id_unused] = current_s_id;
    s_id_to_b_id[current_s_id] = b_id_unused;
    current_s_id++;
    if (b_id_0 != b_id_unused) {
        b_id_to_s_id[b_id_0] = current_s_id;
        s_id_to_b_id[current_s_id] = b_id_0;
        current_s_id++;
    }
    for (int b_id = 0; b_id < M; ++b_id) {
        if (b_id_to_s_id.find(b_id) == b_id_to_s_id.end()) {
            b_id_to_s_id[b_id] = current_s_id;
            s_id_to_b_id[current_s_id] = b_id;
            current_s_id++;
        }
    }
    int C = max(2, (int)ceil(sqrt(M))); 
    int Q = max(1, (int)ceil((double)M / C));

    // --- 4. Phase 3: 初期盤面 ---
    vector<vector<int>> initial_board(N, vector<int>(N, 0)); 
    map<pair<int, int>, bool> has_been_set;
    for (int t = 0; t <= X_global; ++t) { 
        pair<int, int> pos = full_path[t];
        if (!has_been_set[pos]) {
            int b_id = behavior_id_of_t[t]; 
            int s_id = b_id_to_s_id[b_id];  
            initial_board[pos.first][pos.second] = s_id % C; 
            has_been_set[pos] = true;
        }
    }

    // --- 5. Phase 4: 遷移規則 ---
    map<int, tuple<int, int, int>> b_id_to_behavior; 
    for (auto const& [behavior, b_id] : memo_behavior_to_id) {
        b_id_to_behavior[b_id] = behavior;
    }
    
    StrategyOutput output;
    output.C = C; output.Q = Q; output.M = M;
    output.board = initial_board; 

    for (int s_id = 0; s_id < M; ++s_id) { 
        int c = s_id % C;
        int q = s_id / C;
        int b_id = s_id_to_b_id[s_id]; 
        auto [D_idx, b_id_next, b_id_next_visit] = b_id_to_behavior[b_id];
        int s_id_next = b_id_to_s_id[b_id_next];
        int s_id_next_visit = b_id_to_s_id[b_id_next_visit];
        int A = s_id_next_visit % C; 
        int S = s_id_next / C;       
        char D = dir_char[D_idx];
        
        Rule rule = {c, q, A, S, D};
        output.rules.push_back(rule);
        output.rule_map[{c, q}] = rule;
    }

    // --- 6. (削除) シミュレーション開始状態は不要 ---
    
    // --- 7. (★修正) 戦略Aのみ、終点とUNUSEDルールを「激しく」変更 ---
    if (use_random_walk_global && K > 1 && M > 1 && b_id_0 != 0 && b_id_to_s_id.count(b_id_0) && behavior_id_of_t.size() > X_global) {
        
        int s_id_t0 = b_id_to_s_id.at(b_id_0);
        int c_t0 = s_id_t0 % C;
        int q_t0 = s_id_t0 / C;

        // 1. 終点 (K-2到達時) のルール (s_id_X) を変更
        int b_id_X = behavior_id_of_t[X_global];
        int s_id_X = b_id_to_s_id.at(b_id_X);
        int c_X = s_id_X % C;
        int q_X = s_id_X / C;

        if (output.rule_map.count({c_X, q_X})) {
             Rule& rule_X = output.rule_map.at({c_X, q_X});
             rule_X.A = c_t0; 
             rule_X.S = q_t0; 
             rule_X.D = 'R';  
        }

        // 2. UNUSED (s_id=0) のルール (c=0, q=0) を変更
        if (output.rule_map.count({0, 0})) {
            Rule& rule_unused = output.rule_map.at({0, 0});
            rule_unused.A = c_t0; 
            rule_unused.S = q_t0; 
            rule_unused.D = 'L';  
        }
        
        output.rules.clear();
        for(auto const& [key, val] : output.rule_map) {
            output.rules.push_back(val);
        }
    }

    return output;
}

/**
 * @brief 戦略のフルシミュレーションを実行 (★ t=0 から T-1 まで)
 * (★ V=K (順序通り) をチェック)
 */
bool run_simulation(
    const StrategyOutput& strategy,
    int N, int T, int K,
    const vector<pair<int, int>>& target, // K個の目的地リスト
    const vector<string>& v, const vector<string>& h
) {
    vector<vector<int>> current_board = strategy.board; // t=0 の初期盤面
    int curr_y = target[0].first;
    int curr_x = target[0].second;
    int curr_q = 0; // t=0 の q

    int next_target_idx = 0; // ★ 次に目指すべき目的地のインデックス
    int V = 0; // ★ 達成した目的地 (V=K がゴール)

    // t=0 から T-1 まで T ステップ実行
    for (int t = 0; t < T; ++t) { 
        
        // ★ 順序通りの目的地チェック
        if (next_target_idx < K) { // ★ 修正: K個すべて見つけるまで
            if (curr_y == target[next_target_idx].first && 
                curr_x == target[next_target_idx].second) {
                
                V++; // 達成
                next_target_idx++; // 次の目的地へ
                
                if (V == K) {
                    return true; // K個すべて達成
                }
            }
        }
        
        // (★ V=K チェックは上記に移動)

        int c = current_board[curr_y][curr_x];
        
        if (strategy.rule_map.find({c, curr_q}) == strategy.rule_map.end()) {
             break; // ルールが存在しない (行動終了)
        }
        
        Rule rule = strategy.rule_map.at({c, curr_q});

        current_board[curr_y][curr_x] = rule.A;
        curr_q = rule.S;
        
        int dir_idx = 0;
        if (rule.D == 'D') dir_idx = 1;
        else if (rule.D == 'L') dir_idx = 2;
        else if (rule.D == 'R') dir_idx = 3;
        else if (rule.D == 'S') dir_idx = 4;
        
        if (dir_idx < 4 && can_move(curr_y, curr_x, dir_idx, N, v, h)) {
            curr_y += dr[dir_idx];
            curr_x += dc[dir_idx];
        }
    }
    
    // Tステップ終了時の最終チェック
    if (next_target_idx < K) { // ★ 修正
        if (curr_y == target[next_target_idx].first && 
            curr_x == target[next_target_idx].second) {
            V++;
        }
    }

    return (V == K);
}

/**
 * @brief 最終的な戦略を出力
 */
void print_strategy(const StrategyOutput& strategy) {
    cout << strategy.C << " " << strategy.Q << " " << strategy.M << endl;
    for (const auto& row : strategy.board) {
        for (size_t j = 0; j < row.size(); ++j) { 
            cout << row[j] << (j == row.size() - 1 ? "" : " "); 
        }
        cout << endl;
    }
    for (const auto& rule : strategy.rules) {
        cout << rule.c << " " << rule.q << " " << rule.A << " " << rule.S << " " << rule.D << endl;
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int N, K, T; cin >> N >> K >> T;
    vector<string> v(N); vector<string> h(N - 1);
    for (int i = 0; i < N; i++) cin >> v[i];
    for (int i = 0; i < N - 1; i++) cin >> h[i];
    vector<pair<int, int>> target(K);
    for (int i = 0; i < K; i++) cin >> target[i].first >> target[i].second;

    // --- Phase 0: オフライン計算 ---
    vector<pair<int, int>> full_path; 
    full_path.push_back(target[0]);
    long long X = 0; 
    bool reachable_bfs = true;
    vector<int> t_at_target(K, 0); 
    
    for (int k = 0; k < K - 1; k++) { 
        pair<int, int> start = target[k]; pair<int, int> end = target[k + 1];
        auto [steps, parent] = runBFS(N, start, end, v, h);
        if (steps == -1) { reachable_bfs = false; break; }
        X += steps;
        t_at_target[k + 1] = X; 
        auto path = reconstruct_path(parent, start, end);
        for (size_t i = 0; i < path.size() - 1; ++i) {
            pair<int, int> p1 = path[i]; pair<int, int> p2 = path[i + 1];
            int dir_idx = 0; 
            if (p2.first - p1.first == 1) dir_idx = 1; 
            else if (p2.second - p1.second == -1) dir_idx = 2; 
            else if (p2.second - p1.second == 1) dir_idx = 3; 
            D_map_global.push_back(dir_idx);
            full_path.push_back(p2);
        }
    }

    if (reachable_bfs == false && K > 1) { 
        cout << 1 << " " << 1 << " " << 0 << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) cout << 0 << (j == N - 1 ? "" : " ");
            cout << endl;
        }
        return 0;
    }

    // 0b. t_next_visit
    map<pair<int, int>, vector<int>> visits_at_coord;
    for (int t = 0; t <= X; ++t) visits_at_coord[full_path[t]].push_back(t);
    t_next_visit_global.resize(X + 1); 
    for (int t = 0; t <= X; ++t) {
        pair<int, int> coord = full_path[t];
        auto& visits = visits_at_coord[coord];
        auto it = lower_bound(visits.begin(), visits.end(), t);
        if (it != visits.end() && next(it) != visits.end()) {
            t_next_visit_global[t] = *next(it); 
        } else {
            t_next_visit_global[t] = -1; 
        }
    }

    if (K == 1) t_last_stop_global = 0;
    else t_last_stop_global = t_at_target[K-2];

    // --- ★ 戦略分岐 ---
    bool use_strategy_A = false;
    
    // --- 戦略B (確実) のシミュレーション ---
    StrategyOutput strategy_B = generate_strategy(false, N, X, full_path, v, h, K);
    bool success_B = run_simulation(
        strategy_B, N, T, K,
        target, // 目的地リスト (t=0 の開始位置も含む)
        v, h
    );

    if (K > 1) {
        // --- 戦略A (でたらめ) のシミュレーション ---
        StrategyOutput strategy_A = generate_strategy(true, N, X, full_path, v, h, K);
        bool success_A = false;
        
        // (t=0 の b_id と K-2 の b_id が同じ場合、
        //  ルール上書きで自己ループになりシミュレーションが壊れるので除外)
        if (strategy_A.M > 1 && behavior_id_of_t.size() > t_last_stop_global && behavior_id_of_t[0] != behavior_id_of_t[t_last_stop_global]) {
            
            success_A = run_simulation(
                strategy_A, N, T, K,
                target, // 目的地リスト
                v, h
            );
        }

        // --- 判定 ---
        if (success_A) {
            use_strategy_A = true; 
        } else if (success_B) {
            use_strategy_A = false;
        } else {
            // 両方失敗 (X > T など)
            use_strategy_A = true;
        }
    } else {
        // K=1 なら B (停止) しかありえない
        use_strategy_A = false;
    }

    // --- 最終出力 ---
    if (use_strategy_A) {
      //cout<<"d"<<endl;
      StrategyOutput final_strategy_A = generate_strategy(true, N, X, full_path, v, h, K); 
      print_strategy(final_strategy_A);
    } else {
      // (strategy_B はシミュレーション時に生成済み)
      //cout<<"k"<<endl;
      print_strategy(strategy_B);
    }

    return 0;
}
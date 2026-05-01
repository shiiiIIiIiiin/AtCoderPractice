#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

struct Command {
    int type, i, j, k;
};

int R = 10;
vector<deque<int>> dep(10), sid(10);
vector<vector<Command>> turns;

// 移動を適用する関数
void apply_move(int type, int i, int j, int k) {
    if (type == 0) { // 出発線 i の末尾 -> 待避線 j の先頭
        vector<int> block;
        for (int x = 0; x < k; ++x) {
            block.push_back(dep[i].back());
            dep[i].pop_back();
        }
        reverse(block.begin(), block.end());
        for (int x = k - 1; x >= 0; --x) {
            sid[j].push_front(block[x]);
        }
    } else { // 待避線 j の先頭 -> 出発線 i の末尾
        for (int x = 0; x < k; ++x) {
            dep[i].push_back(sid[j].front());
            sid[j].pop_front();
        }
    }
}

// ターンを記録して適用
void add_turn(vector<Command> cmds) {
    if (cmds.empty()) return;
    for (auto& c : cmds) apply_move(c.type, c.i, c.j, c.k);
    turns.push_back(cmds);
}

// LIS (最長増加部分列) を用いて、交差しない最大のペア集合を抽出する関数
// candidates: {元のインデックス, 移動先のインデックス}
vector<pair<int, int>> get_lis(const vector<pair<int, int>>& candidates) {
    vector<pair<int, int>> best_moves;
    int n = candidates.size();
    
    // N <= 10 なのでビット全探索で最適解を確実に見つける
    for (int mask = 1; mask < (1 << n); ++mask) {
        vector<pair<int, int>> current_moves;
        bool valid = true;
        int last_dst = -1;
        for (int bit = 0; bit < n; ++bit) {
            if (mask & (1 << bit)) {
                // 交差制約: 行き先も単調増加でなければならない（同じ行き先もNG）
                if (candidates[bit].second <= last_dst) {
                    valid = false;
                    break;
                }
                last_dst = candidates[bit].second;
                current_moves.push_back(candidates[bit]);
            }
        }
        if (valid && current_moves.size() > best_moves.size()) {
            best_moves = current_moves;
        }
    }
    return best_moves;
}

int main() {
    // 入力
    cin >> R;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < 10; ++j) {
            int id;
            cin >> id;
            dep[i].push_back(id);
        }
    }

    // Phase 1: LISによる大分類（出発線 -> 待避線）
    while (true) {
        vector<pair<int, int>> cands;
        for (int i = 0; i < 10; ++i) {
            if (!dep[i].empty()) {
                int j = dep[i].back() / 10; // 目的地の待避線
                cands.push_back({i, j});
            }
        }
        if (cands.empty()) break; // 全車両が待避線に移動完了
        
        auto best = get_lis(cands);
        vector<Command> cmds;
        for (auto p : best) cmds.push_back({0, p.first, p.second, 1});
        add_turn(cmds);
    }

    // 各出発線が次に受け入れるべき車両のIDを管理
    int next_car[10];
    for (int i = 0; i < 10; ++i) next_car[i] = i * 10;

    // Phase 2: 並列配置とダイナミック退避
    while (true) {
        bool all_done = true;
        for (int i = 0; i < 10; ++i) {
            if (next_car[i] < i * 10 + 10) all_done = false;
        }
        if (all_done) break;

        // [ステップ A] 今すぐ配置できる車両を全待避線から探し、並列移動する
        vector<pair<int, int>> place_cands; // {待避線j, 出発線i}
        for (int j = 0; j < 10; ++j) {
            if (sid[j].empty()) continue;
            int car = sid[j].front();
            int target_i = car / 10;
            if (car == next_car[target_i]) {
                place_cands.push_back({j, target_i});
            }
        }

        if (!place_cands.empty()) {
            auto best = get_lis(place_cands);
            vector<Command> cmds;
            for (auto p : best) {
                cmds.push_back({1, p.second, p.first, 1});
                next_car[p.second]++;
            }
            add_turn(cmds);
            continue; // 並列配置が成功した場合は、状況が変わったのでもう一度並列配置を試す
        }

        // [ステップ B] 並列配置できるものが無い場合、最も浅い(掘り出しやすい)ターゲットを探す
        int best_r = -1, best_sj = -1, min_depth = 999;
        
        for (int r = 0; r < 10; ++r) {
            if (next_car[r] == r * 10 + 10) continue;
            int target = next_car[r];
            
            for (int j = 0; j < 10; ++j) {
                for (int d = 0; d < sid[j].size(); ++d) {
                    if (sid[j][d] == target) {
                        if (d > 0 && d < min_depth) {
                            min_depth = d;
                            best_r = r;
                            best_sj = j;
                        }
                        break;
                    }
                }
            }
        }

        // 掘り出し処理 (退避 -> 目的の車を移動 -> 退避を復元)
        int depth = min_depth;
        int sj = best_sj;
        int r = best_r;

        // 動的に空き容量を持つ出発線(バッファ)を確保
        vector<pair<int, int>> scratch_moves; // {退避先の出発線, 台数}
        int remain = depth;
        for (int k = 0; k < 10; ++k) {
            if (k == r) continue; // 目的の出発線は使わない
            int cap = 15 - dep[k].size();
            if (cap > 0) {
                int take = min(remain, cap);
                scratch_moves.push_back({k, take});
                remain -= take;
                if (remain == 0) break;
            }
        }

        // 1. 邪魔な車両を退避
        for (auto sm : scratch_moves) {
            add_turn({{1, sm.first, sj, sm.second}});
        }
        // 2. 目的の車両を配置
        add_turn({{1, r, sj, 1}});
        next_car[r]++;
        // 3. 退避した車両を逆順で復元（元の順序を維持）
        for (int i = scratch_moves.size() - 1; i >= 0; --i) {
            add_turn({{0, scratch_moves[i].first, sj, scratch_moves[i].second}});
        }
    }

    // 出力
    cout << turns.size() << endl;
    for (const auto& t : turns) {
        cout << t.size() << endl;
        for (const auto& c : t) {
            cout << c.type << " " << c.i << " " << c.j << " " << c.k << endl;
        }
    }

    return 0;
}
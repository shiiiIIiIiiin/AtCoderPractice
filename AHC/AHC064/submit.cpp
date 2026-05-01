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
vector<Command> all_moves;

void apply_move(int type, int i, int j, int k) {
    if (type == 0) { // Dep i -> Sid j
        vector<int> block;
        for (int x = 0; x < k; ++x) {
            block.push_back(dep[i].back());
            dep[i].pop_back();
        }
        reverse(block.begin(), block.end());
        for (int x = k - 1; x >= 0; --x) {
            sid[j].push_front(block[x]);
        }
    } else { // Sid j -> Dep i
        for (int x = 0; x < k; ++x) {
            dep[i].push_back(sid[j].front());
            sid[j].pop_front();
        }
    }
}

void record_move(int type, int i, int j, int k) {
    apply_move(type, i, j, k);
    all_moves.push_back({type, i, j, k});
}

// DAGパッキング
vector<vector<Command>> compress(const vector<Command>& moves) {
    vector<vector<Command>> packed;
    vector<int> last_dep(10, -1), last_sid(10, -1);

    for (const auto& m : moves) {
        int start_t = max(last_dep[m.i], last_sid[m.j]) + 1;
        int t = start_t;
        while (true) {
            if (t >= (int)packed.size()) packed.resize(t + 1);
            bool ok = true;
            for (const auto& exist : packed[t]) {
                if (exist.i == m.i || exist.j == m.j) { ok = false; break; }
                if (1LL * (exist.i - m.i) * (exist.j - m.j) < 0) { ok = false; break; }
            }
            if (ok) {
                packed[t].push_back(m);
                last_dep[m.i] = last_sid[m.j] = t;
                break;
            }
            t++;
        }
    }
    return packed;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    if (!(cin >> R)) return 0;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < 10; ++j) {
            int id; cin >> id;
            dep[i].push_back(id);
        }
    }

    // --- Phase 1: 分配（交互レーンスキャン） ---
    bool forward_p1 = true;
    bool changed = true;
    while (changed) {
        changed = false;
        for (int idx = 0; idx < 10; ++idx) {
            int i = forward_p1 ? idx : 9 - idx;
            if (!dep[i].empty()) {
                int id = dep[i].back();
                record_move(0, i, id % 10, 1);
                changed = true;
            }
        }
        forward_p1 = !forward_p1; // 1台ずつ配る方向を反転
    }

    // --- Phase 2: 回収（交互要求スキャン） ---
    vector<int> next_val(10);
    for (int i = 0; i < 10; ++i) next_val[i] = i * 10; // 各列が次に欲しがっているID

    int finished = 0;
    bool forward_p2 = true;
    while (finished < 100) {
        bool progress = false;
        for (int idx = 0; idx < 10; ++idx) {
            int i = forward_p2 ? idx : 9 - idx; // 要求する出発線のスキャン順を反転
            
            if (next_val[i] < (i + 1) * 10) {
                int target_id = next_val[i];
                int j = target_id % 10; // そのIDが眠っている待避所
                
                // もしそのIDが待避所の先頭にあれば回収
                if (!sid[j].empty() && sid[j].front() == target_id) {
                    record_move(1, i, j, 1);
                    next_val[i]++;
                    finished++;
                    progress = true;
                }
            }
        }
        forward_p2 = !forward_p2; // 回収の波を反転
        
        // 万が一、交互スキャンで進展がなければ（基数ソートならあり得ないが）
        // 全待避所をチェックして動かせるものを探す等の処理が必要だが、
        // 安定な基数ソートの性質上、ここでは必ずprogressする。
        if (!progress && finished < 100) {
            // 安全策：動かせるものを1つ探す
            bool emergency = false;
            for(int j=0; j<10; ++j) {
                if(!sid[j].empty()) {
                    int id = sid[j].front();
                    if(id == next_val[id/10]) {
                        record_move(1, id/10, j, 1);
                        next_val[id/10]++; finished++; emergency = true; break;
                    }
                }
            }
            if(!emergency) break; // 詰み
        }
    }

    // パッキングして出力
    auto final_turns = compress(all_moves);

    cout << final_turns.size() << "\n";
    for (const auto& t_cmds : final_turns) {
        cout << t_cmds.size() << "\n";
        for (const auto& c : t_cmds) {
            cout << c.type << " " << c.i << " " << c.j << " " << c.k << "\n";
        }
    }

    return 0;
}
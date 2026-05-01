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

// DAGパッキング（前回と同じ）
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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> R)) return 0;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < 10; ++j) {
            int id; cin >> id;
            dep[i].push_back(id);
        }
    }

    // Phase 1: 基数ソート 1パス目（1の位で分配）
    // DAG圧縮の並列度を上げるため、10本の出発線を均等に1台ずつ処理する
    bool changed = true;
    while (changed) {
        changed = false;
        for (int i = 0; i < 10; ++i) {
            if (!dep[i].empty()) {
                int id = dep[i].back();
                int target_sid = id % 10;
                record_move(0, i, target_sid, 1);
                changed = true;
            }
        }
    }

    // Phase 2: 基数ソート 2パス目（10の位で回収）
    // 【重要】必ず待避線0から順番に処理しきることで、出発線に0,1,2...の順で届く
    for (int j = 0; j < 10; ++j) {
        while (!sid[j].empty()) {
            int id = sid[j].front();
            int target_dep = id / 10;
            record_move(1, target_dep, j, 1);
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
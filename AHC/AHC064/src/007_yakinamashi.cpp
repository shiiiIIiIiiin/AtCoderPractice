#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

struct Command {
    int type, i, j, k, id;
};

struct Simulation {
    int R;
    vector<deque<int>> dep, sid;
    vector<Command> moves;
    int cmd_count = 0;

    Simulation(int r, const vector<deque<int>>& d) : R(r), dep(d), sid(10) {}

    void apply_move(int type, int i, int j, int k) {
        if (type == 0) { // Dep i -> Sid j
            vector<int> block;
            for (int x = 0; x < k; ++x) {
                block.push_back(dep[i].back());
                dep[i].pop_back();
            }
            reverse(block.begin(), block.end());
            for (int x = k - 1; x >= 0; --x) sid[j].push_front(block[x]);
        } else { // Sid j -> Dep i
            for (int x = 0; x < k; ++x) {
                dep[i].push_back(sid[j].front());
                sid[j].pop_front();
            }
        }
        moves.push_back({type, i, j, k, cmd_count++});
    }
};

// 全探索による最大並列化パッキング (依存関係を厳守)
vector<vector<Command>> compress_exhaustive(const vector<Command>& moves) {
    int N = moves.size();
    vector<int> dep_idx(10, 0), sid_idx(10, 0);
    vector<vector<int>> dep_cmds(10), sid_cmds(10);
    for (int i = 0; i < N; ++i) {
        dep_cmds[moves[i].i].push_back(i);
        sid_cmds[moves[i].j].push_back(i);
    }

    vector<bool> done(N, false);
    vector<vector<Command>> packed;
    int finished = 0;

    while (finished < N) {
        vector<int> candidates;
        for (int i = 0; i < N; ++i) {
            if (done[i]) continue;
            bool d_ok = (dep_idx[moves[i].i] < dep_cmds[moves[i].i].size() && i == dep_cmds[moves[i].i][dep_idx[moves[i].i]]);
            bool s_ok = (sid_idx[moves[i].j] < sid_cmds[moves[i].j].size() && i == sid_cmds[moves[i].j][sid_idx[moves[i].j]]);
            if (d_ok && s_ok) candidates.push_back(i);
            if (candidates.size() >= 10) break;
        }

        int best_mask = 0, max_cmds = 0;
        int K = candidates.size();
        for (int mask = 1; mask < (1 << K); ++mask) {
            vector<int> subset;
            for (int i = 0; i < K; ++i) if ((mask >> i) & 1) subset.push_back(candidates[i]);
            bool ok = true;
            for (int a = 0; a < (int)subset.size(); ++a) {
                for (int b = a + 1; b < (int)subset.size(); ++b) {
                    const auto& m1 = moves[subset[a]];
                    const auto& m2 = moves[subset[b]];
                    if (m1.i == m2.i || m1.j == m2.j) { ok = false; break; }
                    if (1LL * (m1.i - m2.i) * (m1.j - m2.j) < 0) { ok = false; break; }
                }
                if (!ok) break;
            }
            int bits = __builtin_popcount(mask);
            if (ok && bits > max_cmds) { max_cmds = bits; best_mask = mask; }
        }

        vector<Command> turn;
        for (int i = 0; i < K; ++i) {
            if ((best_mask >> i) & 1) {
                int idx = candidates[i];
                turn.push_back(moves[idx]);
                done[idx] = true;
                dep_idx[moves[idx].i]++;
                sid_idx[moves[idx].j]++;
                finished++;
            }
        }
        packed.push_back(turn);
    }
    return packed;
}

vector<vector<Command>> solve(int R, const vector<deque<int>>& initial_dep, const vector<int>& p1) {
    Simulation sim(R, initial_dep);

    // Phase 1: 分配 (k >= 1 の塊移動を活用)
    bool changed = true;
    while (changed) {
        changed = false;
        for (int i : p1) {
            if (sim.dep[i].empty()) continue;
            int target = sim.dep[i].back() % 10;
            int k = 1;
            // 木村さんのアイデア：同じグループが並んでいたら塊で送る
            while (k < (int)sim.dep[i].size() && sim.dep[i][sim.dep[i].size()-1-k] % 10 == target) k++;
            sim.apply_move(0, i, target, k);
            changed = true;
        }
    }

    // Phase 2: 欲張りインターリーブ回収 (正当性を守りつつ並列度最大化)
    vector<int> next_val(10);
    for (int i = 0; i < 10; ++i) next_val[i] = i * 10;

    bool active = true;
    while (active) {
        active = false;
        // どの待避線でもいいから、どこかの目的地が次に欲しがっている数字を探す
        for (int j = 0; j < 10; ++j) {
            if (sim.sid[j].empty()) continue;
            int car_id = sim.sid[j].front();
            int target_line = car_id / 10;
            if (car_id == next_val[target_line]) {
                sim.apply_move(1, target_line, j, 1);
                next_val[target_line]++;
                active = true;
                // 見つかったら一旦仕切り直して、より並列化しやすい候補を探す
            }
        }
    }
    return compress_exhaustive(sim.moves);
}

int main() {
    auto start_time = chrono::system_clock::now();
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int R; cin >> R;
    vector<deque<int>> initial_dep(10);
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < 10; ++j) {
            int id; cin >> id; initial_dep[i].push_back(id);
        }
    }
    mt19937 engine(42);
    vector<int> p1(10); for (int i = 0; i < 10; ++i) p1[i] = i;

    vector<vector<Command>> best_turns = solve(R, initial_dep, p1);
    int best_score = (int)best_turns.size();

    int iter = 0;
    while (true) {
        if (iter % 10 == 0) {
            auto now = chrono::system_clock::now();
            if (chrono::duration_cast<chrono::milliseconds>(now - start_time).count() > 1850) break;
        }
        vector<int> next_p1 = p1;
        shuffle(next_p1.begin(), next_p1.end(), engine);
        auto current_turns = solve(R, initial_dep, next_p1);
        if ((int)current_turns.size() < best_score) {
            best_score = (int)current_turns.size();
            best_turns = current_turns;
            p1 = next_p1;
        }
        iter++;
    }

    cout << best_turns.size() << "\n";
    for (const auto& t : best_turns) {
        cout << t.size() << "\n";
        for (const auto& c : t) cout << c.type << " " << c.i << " " << c.j << " " << c.k << "\n";
    }
    return 0;
}
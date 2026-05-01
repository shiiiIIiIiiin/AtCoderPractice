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
        if (type == 0) {
            vector<int> block;
            for (int x = 0; x < k; ++x) {
                block.push_back(dep[i].back());
                dep[i].pop_back();
            }
            reverse(block.begin(), block.end());
            for (int x = k - 1; x >= 0; --x) sid[j].push_front(block[x]);
        } else {
            for (int x = 0; x < k; ++x) {
                dep[i].push_back(sid[j].front());
                sid[j].pop_front();
            }
        }
        moves.push_back({type, i, j, k, cmd_count++});
    }
};

// 全探索パッキング (交差判定: (i1-i2)*(j1-j2) < 0)
vector<vector<Command>> compress_exhaustive(int R, const vector<Command>& moves) {
    int N = moves.size();
    vector<int> dep_idx(R, 0), sid_idx(10, 0);
    vector<vector<int>> dep_cmds(R), sid_cmds(10);
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
            bool d_ok = (dep_idx[moves[i].i] < (int)dep_cmds[moves[i].i].size() && i == dep_cmds[moves[i].i][dep_idx[moves[i].i]]);
            bool s_ok = (sid_idx[moves[i].j] < (int)sid_cmds[moves[i].j].size() && i == sid_cmds[moves[i].j][sid_idx[moves[i].j]]);
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
                    const auto& m1 = moves[subset[a]], &m2 = moves[subset[b]];
                    if (m1.i == m2.i || m1.j == m2.j || 1LL * (m1.i - m2.i) * (m1.j - m2.j) < 0) { ok = false; break; }
                }
                if (!ok) break;
            }
            if (ok && (int)__builtin_popcount(mask) > max_cmds) { max_cmds = __builtin_popcount(mask); best_mask = mask; }
        }
        vector<Command> turn;
        if (best_mask == 0 && !candidates.empty()) best_mask = 1;
        for (int i = 0; i < K; ++i) {
            if ((best_mask >> i) & 1) {
                int idx = candidates[i]; turn.push_back(moves[idx]);
                done[idx] = true; dep_idx[moves[idx].i]++; sid_idx[moves[idx].j]++; finished++;
            }
        }
        packed.push_back(turn);
    }
    return packed;
}

vector<vector<Command>> solve(int R, const vector<deque<int>>& initial_dep, const vector<int>& p1) {
    Simulation sim(R, initial_dep);
    
    // Phase 1: 分配 (交互走査)
    bool changed = true;
    bool forward_p1 = true;
    while (changed) {
        changed = false;
        vector<int> current_p1 = p1;
        if (!forward_p1) reverse(current_p1.begin(), current_p1.end());
        forward_p1 = !forward_p1;
        for (int i : current_p1) {
            if (sim.dep[i].empty()) continue;
            int target = sim.dep[i].back() % 10;
            int k = 1;
            while (k < (int)sim.dep[i].size() && sim.dep[i][sim.dep[i].size()-1-k] % 10 == target) k++;
            sim.apply_move(0, i, target, k);
            changed = true;
        }
    }

    // Phase 2: 回収 (交互走査)
    vector<int> next_digit_needed(R, 0);
    int total_finished = 0;
    bool forward_p2 = true;
    while (total_finished < R * 10) {
        bool progress = false;
        
        // 理想的な移動の走査
        vector<int> lanes(R);
        for(int i=0; i<R; ++i) lanes[i] = i;
        if(!forward_p2) reverse(lanes.begin(), lanes.end());

        for (int i : lanes) {
            int d = next_digit_needed[i];
            if (d < 10 && !sim.sid[d].empty() && sim.sid[d].front() / 10 == i) {
                sim.apply_move(1, i, d, 1);
                next_digit_needed[i]++;
                total_finished++;
                progress = true;
            }
        }

        // 進展がない場合のフォールバック（待避所の順次処理）
        if(!progress) {
            vector<int> sidings = {0,1,2,3,4,5,6,7,8,9};
            if(!forward_p2) reverse(sidings.begin(), sidings.end());
            
            for(int j : sidings) {
                if(!sim.sid[j].empty()) {
                    int id = sim.sid[j].front();
                    sim.apply_move(1, id / 10, j, 1);
                    next_digit_needed[id / 10]++;
                    total_finished++;
                    progress = true;
                    // ここで break しないことで、複数の待避所から同時に出す手順を moves に並べる
                }
            }
        }
        forward_p2 = !forward_p2;
        if (!progress) break; 
    }
    return compress_exhaustive(R, sim.moves);
}

int main() {
    auto start_time = chrono::system_clock::now();
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int R; cin >> R;
    vector<deque<int>> initial_dep(R);
    for (int i = 0; i < R; ++i) for (int j = 0; j < 10; ++j) {
        int id; cin >> id; initial_dep[i].push_back(id);
    }
    mt19937 engine(42);
    vector<int> p1(R);
    for (int i = 0; i < R; ++i) p1[i] = i;
    
    vector<vector<Command>> best_turns = solve(R, initial_dep, p1);
    int best_score = (int)best_turns.size();
    int iter = 0;
    while (true) {
        if (iter % 10 == 0) {
            if (chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start_time).count() > 1900) break;
        }
        vector<int> next_p1 = p1;
        shuffle(next_p1.begin(), next_p1.end(), engine);
        auto current_turns = solve(R, initial_dep, next_p1);
        if (!current_turns.empty() && (int)current_turns.size() < best_score) {
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
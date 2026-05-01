#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

struct Command {
    int type, i, j, k;
};

struct Simulation {
    int R;
    vector<deque<int>> dep, sid;
    vector<Command> moves;

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
        moves.push_back({type, i, j, k});
    }
};

vector<vector<Command>> compress(const vector<Command>& moves) {
    vector<vector<Command>> packed;
    vector<int> last_dep(10, -1), last_sid(10, -1);
    for (const auto& m : moves) {
        int t = max(last_dep[m.i], last_sid[m.j]) + 1;
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

vector<vector<Command>> solve(int R, const vector<deque<int>>& initial_dep, const vector<int>& p1, const vector<int>& p2) {
    Simulation sim(R, initial_dep);

    // Phase 1: まとめ送り (k >= 1)
    bool changed = true;
    while (changed) {
        changed = false;
        for (int i : p1) {
            if (sim.dep[i].empty()) continue;
            int target = sim.dep[i].back() % 10;
            int k = 1;
            while (k < (int)sim.dep[i].size() && sim.dep[i][sim.dep[i].size()-1-k] % 10 == target) k++;
            sim.apply_move(0, i, target, k);
            changed = true;
        }
    }

    // Phase 2: インターリーブ回収
    // 待避線を横断的に回ることで、行き先の出発線を分散させ並列度を稼ぐ
    bool active = true;
    while (active) {
        active = false;
        for (int j : p2) {
            if (!sim.sid[j].empty()) {
                int id = sim.sid[j].front();
                sim.apply_move(1, id / 10, j, 1);
                active = true;
            }
        }
    }
    return compress(sim.moves);
}

int main() {
    auto start_time = chrono::system_clock::now();
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int R; cin >> R;
    vector<deque<int>> initial_dep(10);
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < 10; ++j) {
            int id; cin >> id;
            initial_dep[i].push_back(id);
        }
    }

    mt19937 engine(42);
    vector<int> p1(10), p2(10);
    for (int i = 0; i < 10; ++i) p1[i] = p2[i] = i;

    vector<vector<Command>> best_turns = solve(R, initial_dep, p1, p2);
    int best_score = (int)best_turns.size();

    int iter = 0;
    while (true) {
        if (iter % 100 == 0) {
            auto now = chrono::system_clock::now();
            if (chrono::duration_cast<chrono::milliseconds>(now - start_time).count() > 1850) break;
        }

        vector<int> next_p1 = p1, next_p2 = p2;
        shuffle(next_p1.begin(), next_p1.end(), engine);
        shuffle(next_p2.begin(), next_p2.end(), engine);

        auto current_turns = solve(R, initial_dep, next_p1, next_p2);
        if ((int)current_turns.size() < best_score) {
            best_score = (int)current_turns.size();
            best_turns = current_turns;
            p1 = next_p1; p2 = next_p2;
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
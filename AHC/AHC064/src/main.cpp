#include<bits/stdc++.h>

using namespace std;

struct Command {
    int type, i, j, k;
};

int R = 10;
vector<deque<int>> dep(10), sid(10);
vector<vector<Command>> turns;

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
    }
    else { // Sid j -> Dep i
        for (int x = 0; x < k; ++x) {
            dep[i].push_back(sid[j].front());
            sid[j].pop_front();
        }
    }
}

void add_turn(vector<Command> cmds) {
    for (auto& c : cmds) apply_move(c.type, c.i, c.j, c.k);
    turns.push_back(cmds);
}

pair<int, int> find_car(int id) {
    for (int j = 0; j < 10; ++j) {
        for (int d = 0; d < sid[j].size(); ++d) {
            if (sid[j][d] == id) return { j, d };
        }
    }
    return { -1, -1 };
}

int main() {
    cin >> R;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < 10; ++j) {
            int id; cin >> id;
            dep[i].push_back(id);
        }
    }

    // Phase 1: All Dep -> Sid
    vector<Command> p1;
    for (int i = 0; i < 10; ++i) p1.push_back({ 0, i, i, 10 });
    add_turn(p1);

    // Phase A: Build Dep 0-8 (Use Dep 9 as scratch)
    for (int c = 0; c < 90; ++c) {
        int target_dep = c / 10;
        pair<int, int> pos = find_car(c);
        int sj = pos.first, depth = pos.second;

        if (depth > 0) add_turn({ {1, 9, sj, depth} });
        add_turn({ {1, target_dep, sj, 1} });
        if (depth > 0) add_turn({ {0, 9, sj, depth} });
    }

    // Phase B: Sort 90-99 into Sid 9 (Use Dep 0, 1 as scratch)
    for (int c = 99; c >= 90; --c) {
        pair<int, int> pos = find_car(c);
        int sj = pos.first, depth = pos.second;

        if (depth > 0) {
            if (depth <= 5) {
                add_turn({ {1, 0, sj, depth} });
            }
            else {
                add_turn({ {1, 0, sj, 5} });
                add_turn({ {1, 1, sj, depth - 5} });
            }
        }

        add_turn({ {1, 9, sj, 1} }); // Move target to Dep 9 temporarily
        add_turn({ {0, 9, 9, 1} }); // Move target to Sid 9 front

        if (depth > 0) {
            if (depth <= 5) {
                add_turn({ {0, 0, sj, depth} });
            }
            else {
                add_turn({ {0, 1, sj, depth - 5} });
                add_turn({ {0, 0, sj, 5} });
            }
        }
    }

    // Phase C: Move Sid 9 to Dep 9
    add_turn({ {1, 9, 9, 10} });

    // Output
    cout << turns.size() << endl;
    for (const auto& t : turns) {
        cout << t.size() << endl;
        for (const auto& c : t) {
            cout << c.type << " " << c.i << " " << c.j << " " << c.k << endl;
        }
    }

    return 0;
}
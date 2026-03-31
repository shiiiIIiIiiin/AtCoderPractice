#include <bits/stdc++.h>
using namespace std;

int N, M, K, T;
vector<vector<int>> adj;
vector<vector<int>> dist;

void bfsAll() {
    dist.assign(N, vector<int>(N, INT_MAX));
    for (int s = 0; s < N; s++) {
        queue<int> q;
        q.push(s);
        dist[s][s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (dist[s][v] == INT_MAX) {
                    dist[s][v] = dist[s][u] + 1;
                    q.push(v);
                }
            }
        }
    }
}

struct State {
    int curPos;
    int prevPos;
    string cone;
    vector<bool> isRed;
    vector<set<string>> shopInventory;
    int score;
    vector<string> actions;
};

// パラメータ
struct Params {
    int maxConeLen;      // この長さになったら配達を目指す
    int rConvertProb;    // R変換確率 (1/n)
    int shopSearchDist;  // ショップを探す距離
};

int simulate(State& st, const Params& params, mt19937& rng) {
    int steps = 0;

    while (steps < T - 10) {
        vector<int> candidates;
        for (int v : adj[st.curPos]) {
            if (v != st.prevPos || adj[st.curPos].size() == 1) {
                candidates.push_back(v);
            }
        }
        if (candidates.empty()) break;

        int next = -1;

        // 1. 配達可能なショップが隣接していれば配達
        if (!st.cone.empty()) {
            for (int v : candidates) {
                if (v < K && !st.shopInventory[v].count(st.cone)) {
                    next = v;
                    break;
                }
            }
        }

        // 2. コーンが十分長い場合、最も近い配達可能ショップに向かう
        if (next == -1 && !st.cone.empty() && (int)st.cone.size() >= params.maxConeLen) {
            int minDist = INT_MAX;
            int targetShop = -1;
            for (int shop = 0; shop < K; shop++) {
                if (!st.shopInventory[shop].count(st.cone) && dist[st.curPos][shop] < minDist) {
                    minDist = dist[st.curPos][shop];
                    targetShop = shop;
                }
            }

            if (targetShop != -1 && minDist <= params.shopSearchDist) {
                // targetShopに向かう最良の隣接頂点
                int bestDist = INT_MAX;
                for (int v : candidates) {
                    if (dist[v][targetShop] < bestDist) {
                        bestDist = dist[v][targetShop];
                        next = v;
                    }
                }
            }
        }

        // 3. コーンが空または短い場合、木に向かう
        if (next == -1) {
            // 木の隣接頂点を優先
            vector<int> treeCandidates;
            for (int v : candidates) {
                if (v >= K) treeCandidates.push_back(v);
            }

            if (!treeCandidates.empty()) {
                // Rの木とWの木のバランスを考慮
                int rTrees = 0, wTrees = 0;
                for (int v : treeCandidates) {
                    if (st.isRed[v]) rTrees++;
                    else wTrees++;
                }

                // 少ない方を優先
                vector<int> preferred;
                if (rTrees < wTrees) {
                    for (int v : treeCandidates) {
                        if (st.isRed[v]) preferred.push_back(v);
                    }
                } else if (wTrees < rTrees) {
                    for (int v : treeCandidates) {
                        if (!st.isRed[v]) preferred.push_back(v);
                    }
                }

                if (!preferred.empty()) {
                    next = preferred[rng() % preferred.size()];
                } else {
                    next = treeCandidates[rng() % treeCandidates.size()];
                }
            }
        }

        // 4. ショップに近い頂点（最短経路上）
        if (next == -1 && !st.cone.empty()) {
            int minDist = INT_MAX;
            for (int shop = 0; shop < K; shop++) {
                if (!st.shopInventory[shop].count(st.cone)) {
                    for (int v : candidates) {
                        if (dist[v][shop] < minDist) {
                            minDist = dist[v][shop];
                            next = v;
                        }
                    }
                }
            }
        }

        // 5. ランダム
        if (next == -1) {
            next = candidates[rng() % candidates.size()];
        }

        // 移動実行
        st.actions.push_back(to_string(next));
        st.prevPos = st.curPos;
        st.curPos = next;
        steps++;

        if (st.curPos >= K) {
            st.cone += (st.isRed[st.curPos] ? 'R' : 'W');

            // R変換
            if (!st.isRed[st.curPos] && steps < T - 10 && params.rConvertProb > 0) {
                if (rng() % params.rConvertProb == 0) {
                    st.actions.push_back("-1");
                    st.isRed[st.curPos] = true;
                    steps++;
                }
            }
        } else {
            if (!st.cone.empty() && !st.shopInventory[st.curPos].count(st.cone)) {
                st.shopInventory[st.curPos].insert(st.cone);
                st.score++;
            }
            st.cone.clear();
        }
    }

    return st.score;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> K >> T;

    adj.assign(N, {});
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> X(K), Y(K);
    for (int i = 0; i < K; i++) {
        cin >> X[i] >> Y[i];
    }

    bfsAll();

    State bestState;
    bestState.score = -1;

    // パラメータ探索
    vector<Params> paramsList = {
        {1, 20, 10},
        {1, 30, 10},
        {1, 50, 10},
        {2, 20, 10},
        {2, 30, 10},
        {2, 50, 10},
        {3, 20, 15},
        {3, 30, 15},
        {3, 50, 15},
    };

    for (const Params& params : paramsList) {
        for (int seed = 0; seed < 20; seed++) {
            State st;
            st.curPos = 0;
            st.prevPos = -1;
            st.cone = "";
            st.isRed.assign(N, false);
            st.shopInventory.assign(K, set<string>());
            st.score = 0;
            st.actions.clear();

            mt19937 rng(seed);
            simulate(st, params, rng);

            if (st.score > bestState.score) {
                bestState = st;
            }
        }
    }

    for (const string& s : bestState.actions) {
        cout << s << "\n";
    }

    return 0;
}

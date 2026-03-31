#include <bits/stdc++.h>
using namespace std;

int N, M, K, T;
vector<vector<int>> adj;

// 各ノードから各店への最短距離
vector<vector<int>> distToShop;
// 各ノードから各木への最短距離
vector<vector<int>> distToTree;
// 各ノードから最寄りの店への距離
vector<int> nearestShopDist;
// 各ノードから最寄りの木への距離
vector<int> nearestTreeDist;

void precomputeDistances() {
    distToShop.assign(K, vector<int>(N, 1e9));
    nearestShopDist.assign(N, 1e9);
    nearestTreeDist.assign(N, 1e9);

    // 各店からBFS
    for (int shop = 0; shop < K; shop++) {
        queue<int> q;
        q.push(shop);
        distToShop[shop][shop] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (distToShop[shop][v] > distToShop[shop][u] + 1) {
                    distToShop[shop][v] = distToShop[shop][u] + 1;
                    q.push(v);
                }
            }
        }
    }

    // 最寄りの店への距離を計算
    for (int i = 0; i < N; i++) {
        for (int shop = 0; shop < K; shop++) {
            nearestShopDist[i] = min(nearestShopDist[i], distToShop[shop][i]);
        }
    }

    // 最寄りの木への距離（マルチソースBFS）
    queue<int> q;
    for (int tree = K; tree < N; tree++) {
        nearestTreeDist[tree] = 0;
        q.push(tree);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (nearestTreeDist[v] > nearestTreeDist[u] + 1) {
                nearestTreeDist[v] = nearestTreeDist[u] + 1;
                q.push(v);
            }
        }
    }
}

struct Params {
    int rProb;        // R変換確率 (1/rProb)
    int goalBias;     // 目的地方向を選ぶ確率 (0-100)
    int exploreProb;  // ランダム探索の確率 (0-100)
};

struct SimResult {
    int score;
    vector<pair<int, string>> actions;
};

// 目的地に近づく隣接ノードを選ぶ
int selectTowardsGoal(int curPos, int goalNode, const vector<int>& candidates, mt19937& rng) {
    if (candidates.empty()) return -1;

    int bestDist = 1e9;
    vector<int> bestCandidates;

    for (int v : candidates) {
        int dist;
        if (goalNode < K) {
            // 店への距離
            dist = distToShop[goalNode][v];
        } else {
            // 木への距離（単純に最寄りの木への距離で代用）
            dist = nearestTreeDist[v];
        }

        if (dist < bestDist) {
            bestDist = dist;
            bestCandidates.clear();
            bestCandidates.push_back(v);
        } else if (dist == bestDist) {
            bestCandidates.push_back(v);
        }
    }

    return bestCandidates[rng() % bestCandidates.size()];
}

// 配達可能な最寄りの店を探す
int findNearestDeliverableShop(int curPos, const string& cone, const vector<set<string>>& shopInventory) {
    int bestShop = -1;
    int bestDist = 1e9;

    for (int shop = 0; shop < K; shop++) {
        if (!shopInventory[shop].count(cone)) {
            int dist = distToShop[shop][curPos];
            if (dist < bestDist) {
                bestDist = dist;
                bestShop = shop;
            }
        }
    }
    return bestShop;
}

// 最寄りの木を探す
int findNearestTree(int curPos, const vector<int>& candidates) {
    int bestTree = -1;
    int bestDist = 1e9;

    for (int v : candidates) {
        if (v >= K && nearestTreeDist[v] == 0) {
            // vは木
            return v;
        }
    }

    // 隣接に木がなければ、最寄りの木方向へ
    for (int v : candidates) {
        if (nearestTreeDist[v] < bestDist) {
            bestDist = nearestTreeDist[v];
            bestTree = v;
        }
    }
    return bestTree;
}

static SimResult simulate(const Params& p, bool recordActions) {
    vector<char> isRed(N, 0);
    vector<set<string>> shopInventory(K);
    string cone;
    int curPos = 0;
    int prevPos = -1;
    int usedSteps = 0;
    int totalScore = 0;
    vector<pair<int, string>> actions;

    mt19937 rng(12345);

    while (usedSteps < T - 10) {
        // 隣接ノード（戻りを避ける）
        vector<int> candidates;
        for (int v : adj[curPos]) {
            if (v != prevPos || adj[curPos].size() == 1) {
                candidates.push_back(v);
            }
        }
        if (candidates.empty() && prevPos != -1) {
            candidates.push_back(prevPos);
        }
        if (candidates.empty()) break;

        int next = candidates[rng() % candidates.size()];  // デフォルトはランダム

        // === 目的地指向型移動 ===
        if ((rng() % 100) < p.goalBias) {
            if (!cone.empty()) {
                // コーンがある → 配達可能な最寄りの店へ
                int targetShop = findNearestDeliverableShop(curPos, cone, shopInventory);
                if (targetShop != -1) {
                    int towards = selectTowardsGoal(curPos, targetShop, candidates, rng);
                    if (towards != -1) next = towards;
                }
            } else {
                // コーンが空 → 最寄りの木へ
                int towards = findNearestTree(curPos, candidates);
                if (towards != -1) next = towards;
            }
        }

        // === 問答無用配達（従来のロジック）===
        // 店を通った時、持っているアイスを店が持っていなければ即配達
        if (!cone.empty()) {
            int bestShop = -1;
            int minInventory = INT_MAX;

            for (int v : candidates) {
                if (v < K && !shopInventory[v].count(cone)) {
                    int invSize = static_cast<int>(shopInventory[v].size());
                    if (invSize < minInventory) {
                        minInventory = invSize;
                        bestShop = v;
                    }
                }
            }

            if (bestShop != -1) {
                next = bestShop;
            }
        }

        if (recordActions) {
            actions.push_back({1, to_string(next)});
        }

        prevPos = curPos;
        curPos = next;

        if (curPos >= K) {
            // 木に到着 → アイス収集
            cone += (isRed[curPos] ? 'R' : 'W');
        } else {
            // 店に到着 → 配達
            if (!cone.empty() && !shopInventory[curPos].count(cone)) {
                shopInventory[curPos].insert(cone);
                totalScore++;
            }
            cone.clear();
        }
        usedSteps++;

        // R変換
        if (curPos >= K && !isRed[curPos]) {
            if (p.rProb > 0 && rng() % p.rProb == 0) {
                if (recordActions) {
                    actions.push_back({2, ""});
                }
                isRed[curPos] = 1;
                usedSteps++;
            }
        }
    }

    return {totalScore, actions};
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

    // 最短距離を事前計算
    precomputeDistances();

    // 初期パラメータ
    Params cur{50, 80, 20};  // rProb, goalBias, exploreProb
    Params best = cur;

    int curScore = simulate(cur, false).score;
    int bestScore = curScore;

    mt19937 rng(42);
    uniform_real_distribution<double> uni(0.0, 1.0);

    // 焼きなまし法
    const double timeLimitSec = 1.95;
    const double t0 = 15.0;
    const double t1 = 0.5;
    const auto start = chrono::high_resolution_clock::now();

    while (true) {
        const auto now = chrono::high_resolution_clock::now();
        double elapsed = chrono::duration<double>(now - start).count();
        if (elapsed >= timeLimitSec) break;
        double progress = elapsed / timeLimitSec;

        Params nxt = cur;
        int which = rng() % 3;
        int delta = (rng() % 2 == 0) ? -1 : 1;

        if (which == 0) {
            nxt.rProb = max(10, min(100, nxt.rProb + delta * 5));
        } else if (which == 1) {
            nxt.goalBias = max(0, min(100, nxt.goalBias + delta * 5));
        } else {
            nxt.exploreProb = max(0, min(50, nxt.exploreProb + delta * 5));
        }

        int nxtScore = simulate(nxt, false).score;

        double t = t0 + (t1 - t0) * progress;
        bool accept = (nxtScore >= curScore);
        if (!accept) {
            double prob = exp((nxtScore - curScore) / t);
            if (uni(rng) < prob) accept = true;
        }

        if (accept) {
            cur = nxt;
            curScore = nxtScore;
            if (curScore > bestScore) {
                bestScore = curScore;
                best = cur;
            }
        }
    }

    SimResult result = simulate(best, true);
    cerr << "Score: " << result.score << "\n";
    cerr << "Params: rProb=" << best.rProb << " goalBias=" << best.goalBias << " exploreProb=" << best.exploreProb << "\n";

    for (auto& [type, arg] : result.actions) {
        if (type == 1) {
            cout << arg << "\n";
        } else {
            cout << "-1\n";
        }
    }

    return 0;
}

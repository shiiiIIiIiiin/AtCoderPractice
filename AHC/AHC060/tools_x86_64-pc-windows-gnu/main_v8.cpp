#include <bits/stdc++.h>
using namespace std;

int N, M, K, T;
vector<vector<int>> adj;

struct Params {
    int rProb;
    int minLen;
    int treeBias;
    int lookDepth;
    int lookBias;
};

struct SimResult {
    int score;
    vector<pair<int, string>> actions;
};

vector<int> findDeliverableMoves(int curPos, const string& cone,
                                  const vector<int>& candidates,
                                  const vector<set<string>>& inv,
                                  const vector<char>& isRed,
                                  int maxDepth) {
    if (cone.empty() || maxDepth <= 0) return {};

    vector<int> goodFirstMoves;

    for (int firstMove : candidates) {
        queue<tuple<int, string, int>> q;
        set<pair<int, string>> visited;

        string cone1 = cone;
        if (firstMove >= K) {
            cone1 += (isRed[firstMove] ? 'R' : 'W');
        }

        if (firstMove < K && !inv[firstMove].count(cone)) {
            goodFirstMoves.push_back(firstMove);
            continue;
        }

        if (firstMove < K) continue;

        q.push({firstMove, cone1, 1});
        visited.insert({firstMove, cone1});

        bool found = false;
        while (!q.empty() && !found) {
            auto [pos, curCone, depth] = q.front();
            q.pop();

            if (depth >= maxDepth) continue;

            for (int next : adj[pos]) {
                string nextCone = curCone;

                if (next < K) {
                    if (!inv[next].count(curCone)) {
                        found = true;
                        break;
                    }
                    continue;
                } else {
                    nextCone += (isRed[next] ? 'R' : 'W');
                }

                if (nextCone.size() > 8) continue;

                if (visited.find({next, nextCone}) == visited.end()) {
                    visited.insert({next, nextCone});
                    q.push({next, nextCone, depth + 1});
                }
            }
        }

        if (found) {
            goodFirstMoves.push_back(firstMove);
        }
    }

    return goodFirstMoves;
}

static int clampInt(int v, int lo, int hi) {
    return max(lo, min(hi, v));
}

static SimResult simulate(const Params& p, bool recordActions, int seed = 12345) {
    vector<char> isRed(N, 0);
    vector<set<string>> shopInventory(K);
    string cone;
    int curPos = 0;
    int prevPos = -1;
    int usedSteps = 0;
    int totalScore = 0;
    vector<pair<int, string>> actions;

    mt19937 rng(seed);

    while (usedSteps < T - 10) {
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

        int next = candidates[rng() % candidates.size()];
        int coneLen = (int)cone.size();

        if (coneLen < p.minLen) {
            vector<int> treeCandidates;
            for (int v : candidates) {
                if (v >= K) treeCandidates.push_back(v);
            }
            if (!treeCandidates.empty() && (rng() % 100) < p.treeBias) {
                next = treeCandidates[rng() % treeCandidates.size()];
            }
        }

        if (!cone.empty()) {
            int bestShop = -1;
            int minInventory = INT_MAX;

            for (int v : candidates) {
                if (v < K && !shopInventory[v].count(cone)) {
                    int invSize = (int)shopInventory[v].size();
                    if (invSize < minInventory) {
                        minInventory = invSize;
                        bestShop = v;
                    }
                }
            }

            if (bestShop != -1) {
                next = bestShop;
            } else if ((rng() % 100) < p.lookBias) {
                vector<int> goodMoves = findDeliverableMoves(
                    curPos, cone, candidates, shopInventory, isRed, p.lookDepth);
                if (!goodMoves.empty()) {
                    next = goodMoves[rng() % goodMoves.size()];
                }
            }
        }

        if (recordActions) {
            actions.push_back({1, to_string(next)});
        }

        prevPos = curPos;
        curPos = next;

        if (curPos >= K) {
            cone += (isRed[curPos] ? 'R' : 'W');
        } else {
            if (!cone.empty() && !shopInventory[curPos].count(cone)) {
                shopInventory[curPos].insert(cone);
                totalScore++;
            }
            cone.clear();
        }
        usedSteps++;

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

    // ===== 多数の戦略候補 =====
    vector<Params> strategies = {
        // 深い先読み系
        {50, 1, 75, 3, 70},
        {50, 1, 75, 4, 80},
        {60, 1, 80, 3, 90},
        // 浅い先読み + 高treeBias
        {50, 1, 90, 2, 80},
        {50, 1, 95, 2, 70},
        // 長いコーン
        {50, 5, 75, 3, 80},
        {50, 6, 70, 2, 90},
        // 短いコーン + 深い先読み
        {50, 1, 70, 4, 90},
        // バランス型
        {55, 2, 80, 3, 75},
        {45, 3, 85, 3, 85},
    };

    mt19937 rng(42);
    uniform_real_distribution<double> uni(0.0, 1.0);

    const double timeLimitSec = 1.90;
    const double t0 = 15.0;
    const double t1 = 0.5;

    // 各戦略に割り当てる時間
    double timePerStrategy = timeLimitSec / strategies.size();

    Params globalBest;
    int globalBestScore = -1;
    int bestStrategyIdx = 0;

    // 全戦略でSAを実行
    for (size_t si = 0; si < strategies.size(); si++) {
        Params cur = strategies[si];
        Params best = cur;
        int curScore = simulate(cur, false).score;
        int bestScore = curScore;

        const auto saStart = chrono::high_resolution_clock::now();
        while (true) {
            const auto now = chrono::high_resolution_clock::now();
            double elapsed = chrono::duration<double>(now - saStart).count();
            if (elapsed >= timePerStrategy) break;
            double progress = elapsed / timePerStrategy;

            Params nxt = cur;
            int which = rng() % 5;
            int delta = (rng() % 2 == 0) ? -1 : 1;

            if (which == 0) {
                nxt.rProb = clampInt(nxt.rProb + delta * 5, 20, 120);
            } else if (which == 1) {
                nxt.minLen = clampInt(nxt.minLen + delta, 1, 6);
            } else if (which == 2) {
                nxt.treeBias = clampInt(nxt.treeBias + delta * 5, 0, 100);
            } else if (which == 3) {
                nxt.lookDepth = clampInt(nxt.lookDepth + delta, 1, 4);
            } else {
                nxt.lookBias = clampInt(nxt.lookBias + delta * 10, 0, 100);
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

        if (bestScore > globalBestScore) {
            globalBestScore = bestScore;
            globalBest = best;
            bestStrategyIdx = si;
        }
    }

    SimResult result = simulate(globalBest, true);
    cerr << "Score: " << result.score << "\n";
    cerr << "Best strategy: " << bestStrategyIdx << "\n";
    cerr << "Params: rProb=" << globalBest.rProb << " minLen=" << globalBest.minLen
         << " treeBias=" << globalBest.treeBias << " lookDepth=" << globalBest.lookDepth
         << " lookBias=" << globalBest.lookBias << "\n";

    for (auto& [type, arg] : result.actions) {
        if (type == 1) {
            cout << arg << "\n";
        } else {
            cout << "-1\n";
        }
    }

    return 0;
}

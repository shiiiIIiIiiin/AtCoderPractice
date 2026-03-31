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

    // ===== より広い戦略候補（30個）=====
    vector<Params> strategies = {
        // 深い先読み系
        {50, 1, 75, 3, 70}, {50, 1, 75, 4, 80}, {60, 1, 80, 3, 90},
        {40, 1, 70, 4, 85}, {55, 1, 85, 4, 75}, {45, 1, 75, 4, 100},
        // 浅い先読み + 高treeBias
        {50, 1, 90, 2, 80}, {50, 1, 95, 2, 70}, {45, 1, 100, 2, 60},
        {55, 1, 85, 2, 90},
        // 長いコーン
        {50, 5, 75, 3, 80}, {50, 6, 70, 2, 90}, {50, 4, 80, 3, 85},
        {50, 3, 85, 3, 90}, {50, 4, 75, 4, 85},
        // 短いコーン + 深い先読み
        {50, 1, 70, 4, 90}, {60, 1, 65, 4, 95}, {40, 1, 75, 4, 100},
        // バランス型
        {55, 2, 80, 3, 75}, {45, 3, 85, 3, 85}, {50, 2, 75, 3, 80},
        {60, 2, 70, 3, 85}, {50, 2, 80, 4, 80},
        // 極端なパラメータ
        {30, 1, 60, 4, 100}, {80, 1, 100, 2, 50},
        {50, 1, 50, 4, 90}, {50, 6, 90, 4, 70},
        // 新規: lookBias=100で先読み最大化
        {50, 1, 70, 4, 100}, {55, 2, 75, 4, 100}, {60, 1, 80, 4, 100},
    };

    mt19937 rng(42);
    uniform_real_distribution<double> uni(0.0, 1.0);

    const double timeLimitSec = 1.90;
    const double t0 = 20.0;  // 温度を少し高めに
    const double t1 = 0.3;

    // Phase 1: 全戦略を1回ずつ評価してTop5を選ぶ
    vector<pair<int, int>> scores;
    for (size_t i = 0; i < strategies.size(); i++) {
        int s = simulate(strategies[i], false).score;
        scores.push_back({s, (int)i});
    }
    sort(scores.rbegin(), scores.rend());

    // Phase 2: Top5戦略でSAを実行
    const int topK = 5;
    double timePerStrategy = timeLimitSec / topK;

    Params globalBest;
    int globalBestScore = -1;

    for (int ti = 0; ti < topK && ti < (int)scores.size(); ti++) {
        int si = scores[ti].second;
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
            // 序盤は大きく探索、終盤は細かく
            int step = (progress < 0.4) ? 2 : 1;
            int delta = (rng() % 2 == 0) ? -step : step;

            if (which == 0) {
                nxt.rProb = clampInt(nxt.rProb + delta * 5, 20, 120);
            } else if (which == 1) {
                nxt.minLen = clampInt(nxt.minLen + delta, 1, 6);
            } else if (which == 2) {
                nxt.treeBias = clampInt(nxt.treeBias + delta * 5, 0, 100);
            } else if (which == 3) {
                nxt.lookDepth = clampInt(nxt.lookDepth + delta, 1, 5);  // 最大5まで許容
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
        }
    }

    SimResult result = simulate(globalBest, true);
    cerr << "Score: " << result.score << "\n";
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

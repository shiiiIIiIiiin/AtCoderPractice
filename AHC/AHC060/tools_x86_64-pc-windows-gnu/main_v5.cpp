#include <bits/stdc++.h>
using namespace std;

int N, M, K, T;
vector<vector<int>> adj;

struct Params {
    int rProb;       // R変換確率
    int minLen;      // 最小コーン長
    int treeBias;    // 木優先確率
    int look2Bias;   // 2手先読み使用確率
};

struct SimResult {
    int score;
    vector<pair<int, string>> actions;
};

// 2手以内に配達可能な店があるかチェック
bool canDeliverIn2Steps(int pos, const string& cone, const vector<set<string>>& inv) {
    if (cone.empty()) return false;

    // 1手目
    for (int v1 : adj[pos]) {
        if (v1 < K && !inv[v1].count(cone)) return true;

        // 2手目
        string cone1 = cone;
        if (v1 >= K) cone1 += 'W';  // 仮にWとする（実際の色は不明だが）

        for (int v2 : adj[v1]) {
            if (v2 < K) {
                // coneを配達できるか（1手目で木を通った場合はcone1）
                if (v1 >= K) {
                    if (!inv[v2].count(cone1)) return true;
                } else {
                    // v1が店の場合、v2では新しいコーンを開始するので関係なし
                }
            }
        }
    }
    return false;
}

// 候補の中で「2手以内に配達できる」ものを返す
vector<int> filterGoodCandidates(int pos, const string& cone,
                                  const vector<int>& candidates,
                                  const vector<set<string>>& inv,
                                  const vector<char>& isRed) {
    if (cone.empty()) return {};

    vector<int> good;
    for (int v : candidates) {
        // vに行った後
        string nextCone = cone;
        if (v >= K) {
            nextCone += (isRed[v] ? 'R' : 'W');
        }

        if (v < K && !inv[v].count(cone)) {
            // 即配達可能
            good.push_back(v);
        } else if (v >= K) {
            // 木に行く場合、次のステップで配達可能な店があるか
            for (int v2 : adj[v]) {
                if (v2 < K && !inv[v2].count(nextCone)) {
                    good.push_back(v);
                    break;
                }
            }
        }
    }
    return good;
}

static int clampInt(int v, int lo, int hi) {
    return max(lo, min(hi, v));
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

        // === 1. コーンが短いときは木を優先 ===
        if (coneLen < p.minLen) {
            vector<int> treeCandidates;
            for (int v : candidates) {
                if (v >= K) treeCandidates.push_back(v);
            }
            if (!treeCandidates.empty() && (rng() % 100) < p.treeBias) {
                next = treeCandidates[rng() % treeCandidates.size()];
            }
        }

        // === 2. 問答無用配達（最優先）===
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
            } else if ((rng() % 100) < p.look2Bias) {
                // === 3. 2手先読み：2手以内に配達できる方向へ ===
                vector<int> goodCands = filterGoodCandidates(curPos, cone, candidates, shopInventory, isRed);
                if (!goodCands.empty()) {
                    next = goodCands[rng() % goodCands.size()];
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

    // 初期パラメータ
    Params cur{50, 1, 75, 50};  // rProb, minLen, treeBias, look2Bias
    Params best = cur;

    int curScore = simulate(cur, false).score;
    int bestScore = curScore;

    mt19937 rng(42);
    uniform_real_distribution<double> uni(0.0, 1.0);

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
        int which = rng() % 4;
        int delta = (rng() % 2 == 0) ? -1 : 1;

        if (which == 0) {
            nxt.rProb = clampInt(nxt.rProb + delta * 5, 20, 120);
        } else if (which == 1) {
            nxt.minLen = clampInt(nxt.minLen + delta, 1, 6);
        } else if (which == 2) {
            nxt.treeBias = clampInt(nxt.treeBias + delta * 5, 0, 100);
        } else {
            nxt.look2Bias = clampInt(nxt.look2Bias + delta * 10, 0, 100);
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
    cerr << "Params: rProb=" << best.rProb << " minLen=" << best.minLen
         << " treeBias=" << best.treeBias << " look2Bias=" << best.look2Bias << "\n";

    for (auto& [type, arg] : result.actions) {
        if (type == 1) {
            cout << arg << "\n";
        } else {
            cout << "-1\n";
        }
    }

    return 0;
}

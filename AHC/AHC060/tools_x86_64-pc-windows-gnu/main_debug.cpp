#include <bits/stdc++.h>
using namespace std;

int N, M, K, T;
vector<vector<int>> adj;

struct Params
{
    int rProb;
    int minLen;
    int treeBias;
    int lookDepth;
    int lookBias;
};

struct SimResult
{
    int score;
    vector<pair<int, string>> actions;
};

// デバッグ用: 状態数カウント
int totalFindCalls = 0;
long long totalStates = 0;
int maxStatesInSingleCall = 0;

vector<int> findDeliverableMoves(int curPos, const string &cone,
                                 const vector<int> &candidates,
                                 const vector<set<string>> &inv,
                                 const vector<char> &isRed,
                                 int maxDepth)
{
    if (cone.empty() || maxDepth <= 0)
        return {};

    constexpr int MAX_STATES = 100000; // さらに増やして確認
    vector<int> goodFirstMoves;
    totalFindCalls++;

    for (int firstMove : candidates)
    {
        queue<tuple<int, string, int>> q;
        set<pair<int, string>> visited;

        string cone1 = cone;
        if (firstMove >= K)
        {
            cone1 += (isRed[firstMove] ? 'R' : 'W');
        }

        if (firstMove < K && !inv[firstMove].count(cone))
        {
            goodFirstMoves.push_back(firstMove);
            continue;
        }

        if (firstMove < K)
            continue;

        q.push({firstMove, cone1, 1});
        visited.insert({firstMove, cone1});

        bool found = false;
        bool hitLimit = false;
        while (!q.empty() && !found)
        {
            if (visited.size() > MAX_STATES)
            {
                hitLimit = true;
                break;
            }

            auto [pos, curCone, depth] = q.front();
            q.pop();

            if (depth >= maxDepth)
                continue;

            for (int next : adj[pos])
            {
                string nextCone = curCone;

                if (next < K)
                {
                    if (!inv[next].count(curCone))
                    {
                        found = true;
                        break;
                    }
                    continue;
                }
                else
                {
                    nextCone += (isRed[next] ? 'R' : 'W');
                }

                if (nextCone.size() > 8)
                    continue;

                if (visited.find({next, nextCone}) == visited.end())
                {
                    visited.insert({next, nextCone});
                    q.push({next, nextCone, depth + 1});
                }
            }
        }

        int statesUsed = visited.size();
        totalStates += statesUsed;
        maxStatesInSingleCall = max(maxStatesInSingleCall, statesUsed);

        if (found)
        {
            goodFirstMoves.push_back(firstMove);
        }
    }

    return goodFirstMoves;
}

static SimResult simulate(const Params &p, bool recordActions)
{
    vector<char> isRed(N, 0);
    vector<set<string>> shopInventory(K);
    string cone;
    int curPos = 0;
    int prevPos = -1;
    int usedSteps = 0;
    int totalScore = 0;
    vector<pair<int, string>> actions;

    mt19937 rng(12345);

    while (usedSteps < T - 10)
    {
        vector<int> candidates;
        for (int v : adj[curPos])
        {
            if (v != prevPos || adj[curPos].size() == 1)
            {
                candidates.push_back(v);
            }
        }
        if (candidates.empty() && prevPos != -1)
        {
            candidates.push_back(prevPos);
        }
        if (candidates.empty())
            break;

        int next = candidates[rng() % candidates.size()];
        int coneLen = static_cast<int>(cone.size());

        if (coneLen < p.minLen)
        {
            vector<int> treeCandidates;
            treeCandidates.reserve(candidates.size());
            for (int v : candidates)
            {
                if (v >= K)
                    treeCandidates.push_back(v);
            }
            if (!treeCandidates.empty() && (rng() % 100) < p.treeBias)
            {
                next = treeCandidates[rng() % treeCandidates.size()];
            }
        }

        if (!cone.empty())
        {
            int bestShop = -1;
            int minInventory = INT_MAX;

            for (int v : candidates)
            {
                if (v < K && !shopInventory[v].count(cone))
                {
                    int invSize = static_cast<int>(shopInventory[v].size());
                    if (invSize < minInventory)
                    {
                        minInventory = invSize;
                        bestShop = v;
                    }
                }
            }

            if (bestShop != -1)
            {
                next = bestShop;
            }
            else if ((rng() % 100) < p.lookBias)
            {
                vector<int> goodMoves = findDeliverableMoves(curPos, cone, candidates, shopInventory, isRed, p.lookDepth);
                if (!goodMoves.empty())
                {
                    next = goodMoves[rng() % goodMoves.size()];
                }
            }
        }

        if (recordActions)
        {
            actions.push_back({1, to_string(next)});
        }

        prevPos = curPos;
        curPos = next;
        if (curPos >= K)
        {
            cone += (isRed[curPos] ? 'R' : 'W');
        }
        else
        {
            if (!cone.empty() && !shopInventory[curPos].count(cone))
            {
                shopInventory[curPos].insert(cone);
                totalScore++;
            }
            cone.clear();
        }
        usedSteps++;

        if (curPos >= K && !isRed[curPos])
        {
            if (p.rProb > 0 && rng() % p.rProb == 0)
            {
                if (recordActions)
                {
                    actions.push_back({2, ""});
                }
                isRed[curPos] = 1;
                usedSteps++;
            }
        }
    }

    return {totalScore, actions};
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> K >> T;

    adj.assign(N, {});
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> X(K), Y(K);
    for (int i = 0; i < K; i++)
    {
        cin >> X[i] >> Y[i];
    }

    vector<Params> candidates = {
        {50, 1, 75, 20, 90},
        {50, 1, 80, 15, 85},
        {50, 1, 70, 10, 80},
        {50, 2, 75, 8, 85},
        {50, 1, 90, 5, 90},
    };

    cerr << "Testing with MAX_STATES=100000...\n\n";

    for (size_t i = 0; i < candidates.size(); i++)
    {
        totalFindCalls = 0;
        totalStates = 0;
        maxStatesInSingleCall = 0;

        auto result = simulate(candidates[i], false);

        double avgStates = totalFindCalls > 0 ? (double)totalStates / totalFindCalls : 0;

        cerr << "depth=" << candidates[i].lookDepth << ":\n";
        cerr << "  score=" << result.score << "\n";
        cerr << "  findCalls=" << totalFindCalls << "\n";
        cerr << "  avgStates=" << fixed << setprecision(1) << avgStates << "\n";
        cerr << "  maxStates=" << maxStatesInSingleCall << "\n\n";
    }

    // ベストパラメータで実行
    Params best = {50, 1, 70, 10, 80};
    SimResult result = simulate(best, true);

    for (auto &[type, arg] : result.actions)
    {
        if (type == 1)
            cout << arg << "\n";
        else
            cout << "-1\n";
    }

    return 0;
}

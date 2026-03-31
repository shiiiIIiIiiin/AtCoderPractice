#include <bits/stdc++.h>
using namespace std;

int N, M, K, T;
vector<vector<int>> adj;

struct Params
{
    int lenLong;
    int lenMid;
    int invMid;
    int lenShort;
    int invShort;
    int rProb;
};

struct SimResult
{
    int score;
    vector<pair<int, string>> actions;
};

static int clampInt(int v, int lo, int hi)
{
    return max(lo, min(hi, v));
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

        if (!cone.empty())
        {
            int bestShop = -1;
            int bestScore = INT_MAX;

            for (int v : candidates)
            {
                if (v < K && !shopInventory[v].count(cone))
                {
                    int invSize = static_cast<int>(shopInventory[v].size());
                    bool shouldDeliver = (static_cast<int>(cone.size()) >= p.lenLong) ||
                                         (static_cast<int>(cone.size()) >= p.lenMid && invSize < p.invMid) ||
                                         (static_cast<int>(cone.size()) >= p.lenShort && invSize < p.invShort);

                    if (shouldDeliver)
                    {
                        int score = invSize * 10 + (p.lenLong + 1 - static_cast<int>(cone.size()));
                        if (score < bestScore)
                        {
                            bestScore = score;
                            bestShop = v;
                        }
                    }
                }
            }

            if (bestShop != -1)
            {
                next = bestShop;
            }
            else if (static_cast<int>(cone.size()) >= p.lenLong && next >= K)
            {
                for (int v : candidates)
                {
                    if (v < K)
                    {
                        next = v;
                        break;
                    }
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

    Params cur{7, 5, 12, 3, 8, 60};
    Params best = cur;

    int curScore = simulate(cur, false).score;
    int bestScore = curScore;

    mt19937 rng(42);
    uniform_real_distribution<double> uni(0.0, 1.0);

    const int iters = 300;
    const double t0 = 20.0;
    const double t1 = 1.0;

    for (int i = 0; i < iters; i++)
    {
        Params nxt = cur;
        int which = rng() % 6;
        int delta = (rng() % 2 == 0) ? -1 : 1;

        if (which == 0)
            nxt.lenLong = clampInt(nxt.lenLong + delta, 6, 9);
        else if (which == 1)
            nxt.lenMid = clampInt(nxt.lenMid + delta, 4, 7);
        else if (which == 2)
            nxt.invMid = clampInt(nxt.invMid + delta * 2, 8, 16);
        else if (which == 3)
            nxt.lenShort = clampInt(nxt.lenShort + delta, 2, 5);
        else if (which == 4)
            nxt.invShort = clampInt(nxt.invShort + delta * 2, 5, 12);
        else
            nxt.rProb = clampInt(nxt.rProb + delta * 5, 30, 90);

        if (nxt.lenMid > nxt.lenLong)
            nxt.lenMid = nxt.lenLong;
        if (nxt.lenShort > nxt.lenMid)
            nxt.lenShort = nxt.lenMid;

        int nxtScore = simulate(nxt, false).score;

        double t = t0 + (t1 - t0) * (static_cast<double>(i) / (iters - 1));
        bool accept = (nxtScore >= curScore);
        if (!accept)
        {
            double prob = exp((nxtScore - curScore) / t);
            if (uni(rng) < prob)
                accept = true;
        }

        if (accept)
        {
            cur = nxt;
            curScore = nxtScore;
            if (curScore > bestScore)
            {
                bestScore = curScore;
                best = cur;
            }
        }
    }

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

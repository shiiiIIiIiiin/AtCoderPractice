#include <bits/stdc++.h>
using namespace std;

int N, M, K, T;
vector<vector<int>> adj;

struct Params
{
    int rProb;  // R変換確率 (1/rProb)
    int minLen; // 最小配達長さ（これ未満は配達しない）
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

        // 日和見配達（minLen以上なら配達）
        if (!cone.empty() && static_cast<int>(cone.size()) >= p.minLen)
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

        // R変換
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

    // 初期パラメータ
    Params cur{57, 1}; // rProb=57, minLen=1 (日和見配達)
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

    while (true)
    {
        const auto now = chrono::high_resolution_clock::now();
        double elapsed = chrono::duration<double>(now - start).count();
        if (elapsed >= timeLimitSec)
            break;
        double progress = elapsed / timeLimitSec;

        Params nxt = cur;
        int which = rng() % 2;
        int delta = (rng() % 2 == 0) ? -1 : 1;

        if (which == 0)
        {
            nxt.rProb = clampInt(nxt.rProb + delta * 3, 30, 100);
        }
        else
        {
            nxt.minLen = clampInt(nxt.minLen + delta, 1, 6);
        }

        int nxtScore = simulate(nxt, false).score;

        double t = t0 + (t1 - t0) * progress;
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
    cerr << "Score: " << result.score << "\n";
    for (auto &[type, arg] : result.actions)
    {
        if (type == 1)
        {
            cout << arg << "\n";
        }
        else
        {
            cout << "-1\n";
        }
    }

    return 0;
}

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

    bool operator<(const Params &other) const
    {
        if (lenLong != other.lenLong)
            return lenLong < other.lenLong;
        if (lenMid != other.lenMid)
            return lenMid < other.lenMid;
        if (invMid != other.invMid)
            return invMid < other.invMid;
        if (lenShort != other.lenShort)
            return lenShort < other.lenShort;
        if (invShort != other.invShort)
            return invShort < other.invShort;
        return rProb < other.rProb;
    }
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

    mt19937 rng(42);
    uniform_real_distribution<double> uni(0.0, 1.0);
    const auto globalStart = chrono::high_resolution_clock::now();

    // ===== Phase 1: Beam Search (0.5 sec) =====
    const double beamTimeLimit = 0.5;
    const int beamWidth = 8;
    vector<pair<int, Params>> beam; // (score, params)

    // Initial beam: create diverse starting points
    vector<Params> initialCandidates = {
        {7, 5, 12, 3, 8, 60},  // V18 baseline
        {8, 6, 14, 4, 10, 50}, // variant 1
        {6, 4, 10, 2, 6, 70},  // variant 2
        {9, 7, 16, 5, 12, 40}, // variant 3
        {7, 5, 12, 3, 8, 60},  // duplicate for diversity
        {8, 5, 13, 3, 9, 55},  // variant 4
        {6, 5, 11, 3, 7, 65},  // variant 5
        {7, 6, 12, 4, 8, 60},  // variant 6
    };

    for (auto &p : initialCandidates)
    {
        int score = simulate(p, false).score;
        beam.push_back({score, p});
    }
    sort(beam.rbegin(), beam.rend());
    if (beam.size() > beamWidth)
        beam.resize(beamWidth);

    // Beam search iterations
    int beamIter = 0;
    while (true)
    {
        auto now = chrono::high_resolution_clock::now();
        double elapsed = chrono::duration<double>(now - globalStart).count();
        if (elapsed >= beamTimeLimit)
            break;

        // Generate neighbors from current beam
        vector<pair<int, Params>> nextBeam;
        for (auto &[curScore, curParams] : beam)
        {
            for (int trial = 0; trial < 3; trial++)
            {
                Params nxt = curParams;
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
                nextBeam.push_back({nxtScore, nxt});
            }
        }

        // Merge and select top beamWidth
        for (auto &p : beam)
            nextBeam.push_back(p);
        sort(nextBeam.rbegin(), nextBeam.rend());
        beam.clear();
        for (int i = 0; i < min((int)nextBeam.size(), beamWidth); i++)
        {
            beam.push_back(nextBeam[i]);
        }

        beamIter++;
    }

    // Select random initial params from beam
    Params cur = beam[rng() % beam.size()].second;
    int curScore = simulate(cur, false).score;
    Params best = cur;
    int bestScore = curScore;

    // ===== Phase 2: Simulated Annealing (1.4 sec) =====
    const double saTimeLimit = 1.4;
    const double t0 = 20.0;
    const double t1 = 1.0;
    const auto saStart = chrono::high_resolution_clock::now();

    int saIter = 0;
    while (true)
    {
        auto now = chrono::high_resolution_clock::now();
        double elapsed = chrono::duration<double>(now - globalStart).count();
        if (elapsed >= beamTimeLimit + saTimeLimit)
            break;

        double saElapsed = chrono::duration<double>(now - saStart).count();
        double saProgress = min(1.0, saElapsed / saTimeLimit);

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

        double t = t0 * pow(t1 / t0, saProgress);
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
        saIter++;
    }

    SimResult result = simulate(best, true);
    cerr << "Score: " << result.score << endl;
    for (auto &[type, arg] : result.actions)
    {
        if (type == 1)
            cout << arg << "\n";
        else
            cout << "-1\n";
    }

    return 0;
}

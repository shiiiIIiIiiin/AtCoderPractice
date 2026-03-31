#include <bits/stdc++.h>
using namespace std;

int N, M, K, T;
vector<vector<int>> adj;
vector<bool> isRed;
vector<set<string>> shopInventory;

int curPos, prevPos;
string cone;
int usedSteps;
vector<pair<int, string>> actions;

void moveTo(int nextPos)
{
    actions.push_back({1, to_string(nextPos)});
    prevPos = curPos;
    curPos = nextPos;
    if (curPos >= K)
    {
        cone += (isRed[curPos] ? 'R' : 'W');
    }
    else
    {
        if (!cone.empty() && !shopInventory[curPos].count(cone))
        {
            shopInventory[curPos].insert(cone);
        }
        cone = "";
    }
    usedSteps++;
}

void changeToRed()
{
    if (curPos >= K && !isRed[curPos])
    {
        actions.push_back({2, ""});
        isRed[curPos] = true;
        usedSteps++;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> K >> T;

    adj.resize(N);
    isRed.resize(N, false);
    shopInventory.resize(K);

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

    curPos = 0;
    prevPos = -1;
    cone = "";
    usedSteps = 0;

    mt19937 rng(42);

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

        // 2フェーズ戦略：前半は探索、後半は最適化
        int phase = usedSteps < T / 2 ? 0 : 1;

        if (!cone.empty())
        {
            int bestShop = -1;
            int minInventory = INT_MAX;

            if (phase == 0)
            {
                // 前半：保守的、長いconeのみ配達
                for (int v : candidates)
                {
                    if (v < K && !shopInventory[v].count(cone))
                    {
                        if (cone.size() >= 8)
                        {
                            int invSize = shopInventory[v].size();
                            if (invSize < minInventory)
                            {
                                minInventory = invSize;
                                bestShop = v;
                            }
                        }
                    }
                }
            }
            else
            {
                // 後半：積極的、長めなら配達
                for (int v : candidates)
                {
                    if (v < K && !shopInventory[v].count(cone))
                    {
                        int invSize = shopInventory[v].size();
                        bool shouldDeliver = (cone.size() >= 6) ||
                                             (cone.size() >= 4 && invSize < 10);
                        if (shouldDeliver && invSize < minInventory)
                        {
                            minInventory = invSize;
                            bestShop = v;
                        }
                    }
                }
            }

            if (bestShop != -1)
            {
                next = bestShop;
            }
        }

        moveTo(next);

        // R-change: フェーズによって確率を変更
        int rChangeProb = (phase == 0) ? 30 : 50; // 前半1/30(積極)、後半1/50(保守)
        if (curPos >= K && !isRed[curPos] && rng() % rChangeProb == 0)
        {
            changeToRed();
        }
    }

    for (auto &[type, arg] : actions)
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

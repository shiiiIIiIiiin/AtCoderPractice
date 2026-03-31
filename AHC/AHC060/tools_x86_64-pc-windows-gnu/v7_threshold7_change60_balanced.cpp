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

        // coneが長い場合、まだ持っていないショップを優先 (しきい値7)
        if (cone.size() >= 7)
        {
            int bestShop = -1;
            int minInventory = INT_MAX;

            for (int v : candidates)
            {
                if (v < K)
                {
                    if (!shopInventory[v].count(cone))
                    {
                        if (shopInventory[v].size() < minInventory)
                        {
                            minInventory = shopInventory[v].size();
                            bestShop = v;
                        }
                    }
                }
            }

            if (bestShop != -1)
            {
                next = bestShop;
            }
            else
            {
                minInventory = INT_MAX;
                for (int v : candidates)
                {
                    if (v < K && shopInventory[v].size() < minInventory)
                    {
                        minInventory = shopInventory[v].size();
                        bestShop = v;
                    }
                }
                if (bestShop != -1)
                {
                    next = bestShop;
                }
            }
        }

        moveTo(next);

        if (curPos >= K && !isRed[curPos] && rng() % 60 == 0)
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

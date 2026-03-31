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

        // 配達判定：短いコーンでも「そのお店にない」なら配達
        if (!cone.empty())
        {
            int bestShop = -1;
            int bestScore = INT_MAX;

            for (int v : candidates)
            {
                if (v < K && !shopInventory[v].count(cone))
                {
                    int invSize = shopInventory[v].size();

                    // 配達条件（より厳選）：
                    // 1. 長いコーン(>=7) → 常に配達
                    // 2. 中程度(>=5) && 在庫<12 → 配達
                    // 3. 短い(>=4) && 在庫が非常に少ない(<7) → 配達
                    bool shouldDeliver = (cone.size() >= 7) ||
                                         (cone.size() >= 5 && invSize < 12) ||
                                         (cone.size() >= 4 && invSize < 7);

                    if (shouldDeliver)
                    {
                        // スコア計算：在庫少ないほど優先、コーン長いほど優先
                        int score = invSize * 100 - cone.size();
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
            else if (cone.size() >= 7 && next >= K)
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

        moveTo(next);

        // R-change確率 1/60
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

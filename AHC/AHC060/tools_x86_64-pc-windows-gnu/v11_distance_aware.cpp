#include <bits/stdc++.h>
using namespace std;

int N, M, K, T;
vector<vector<int>> adj;
vector<bool> isRed;
vector<set<string>> shopInventory;
vector<int> X, Y;

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

int dist(int a, int b)
{
    long long dx = X[a] - X[b];
    long long dy = Y[a] - Y[b];
    return (int)sqrt(dx * dx + dy * dy);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> K >> T;

    adj.resize(N);
    isRed.resize(N, false);
    shopInventory.resize(K);
    X.resize(K);
    Y.resize(K);

    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

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

        // 配達判定：距離を考慮した在庫バランス
        if (!cone.empty())
        {
            int bestShop = -1;
            int bestScore = INT_MAX;

            for (int v : candidates)
            {
                if (v < K && !shopInventory[v].count(cone))
                {
                    int invSize = shopInventory[v].size();
                    bool shouldDeliver = (cone.size() >= 7) ||
                                         (cone.size() >= 5 && invSize < 12);
                    if (shouldDeliver)
                    {
                        // スコア = 在庫サイズ + 距離(大きいほど遠い)
                        int score = invSize * 100 + dist(0, v);
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
                // 長いコーンでショップが見つからなければ任意のショップ
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

        // R-change: フェーズに応じて確率を変更
        int rChangeProb = (usedSteps < T / 2) ? 40 : 50; // 前半1/40、後半1/50
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

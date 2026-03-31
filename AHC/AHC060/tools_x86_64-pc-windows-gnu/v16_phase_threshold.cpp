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

    // フェーズ境界
    int midPhase = (2 * T) / 3;

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

        // 配達判定：フェーズによって閾値を変更
        if (!cone.empty())
        {
            int bestShop = -1;
            int minInventory = INT_MAX;

            // 前半（0 ~ 2T/3）：積極的（閾値6）
            // 後半（2T/3 ~ T）：保守的（閾値8）
            int deliveryThreshold = (usedSteps < midPhase) ? 6 : 8;

            for (int v : candidates)
            {
                if (v < K && !shopInventory[v].count(cone))
                {
                    int invSize = shopInventory[v].size();
                    bool shouldDeliver = (cone.size() >= deliveryThreshold);
                    if (shouldDeliver && invSize < minInventory)
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
            else if (cone.size() >= deliveryThreshold && next >= K)
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

        // R-change確率：フェーズによって変更
        int rChangeProb = (usedSteps < midPhase) ? 50 : 65; // 前半1/50、後半1/65
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

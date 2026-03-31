#include <bits/stdc++.h>
using namespace std;

int N, M, K, T;
vector<vector<int>> adj;
vector<vector<int>> dist;

// BFSで全点間最短距離を計算
void calcDist()
{
    dist.assign(N, vector<int>(N, 1e9));
    for (int s = 0; s < N; s++)
    {
        queue<int> q;
        q.push(s);
        dist[s][s] = 0;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int v : adj[u])
            {
                if (dist[s][v] > dist[s][u] + 1)
                {
                    dist[s][v] = dist[s][u] + 1;
                    q.push(v);
                }
            }
        }
    }
}

// パターンを作るのに必要な木の色を取得
vector<char> getRequiredColors(const string &pattern)
{
    vector<char> colors;
    for (char c : pattern)
        colors.push_back(c);
    return colors;
}

// 現在位置からパターンを作るコストを計算
int calcPatternCost(int curPos, const string &pattern, const vector<char> &isRed)
{
    int cost = 0;
    int pos = curPos;

    for (char c : pattern)
    {
        // 必要な色の木を探す
        int bestTree = -1;
        int bestDist = 1e9;
        for (int v = K; v < N; v++)
        {
            char treeColor = isRed[v] ? 'R' : 'W';
            if (treeColor == c && dist[pos][v] < bestDist)
            {
                bestDist = dist[pos][v];
                bestTree = v;
            }
        }
        if (bestTree == -1)
            return 1e9;
        cost += bestDist;
        pos = bestTree;
    }
    return cost;
}

// パターンを作成して配達（実際に移動しながら）
pair<vector<int>, bool> createAndDeliver(int &curPos, const string &pattern, int targetShop,
                                         vector<char> &isRed, string &currentCone, mt19937 &rng, int rProb)
{
    vector<int> moves;
    currentCone.clear();

    for (char c : pattern)
    {
        // 必要な色の木を探す
        int bestTree = -1;
        int bestDist = 1e9;
        for (int v = K; v < N; v++)
        {
            char treeColor = isRed[v] ? 'R' : 'W';
            if (treeColor == c && dist[curPos][v] < bestDist)
            {
                bestDist = dist[curPos][v];
                bestTree = v;
            }
        }

        if (bestTree == -1)
            return {{}, false};

        // 最短経路で移動
        while (curPos != bestTree)
        {
            int next = -1;
            for (int v : adj[curPos])
            {
                if (dist[v][bestTree] < dist[curPos][bestTree])
                {
                    next = v;
                    break;
                }
            }
            if (next == -1)
                return {{}, false};
            moves.push_back(next);
            curPos = next;

            // 移動先が店なら配達してリセット
            if (curPos < K)
            {
                currentCone.clear();
            }
        }

        // 木に到着、アイス追加
        currentCone += (isRed[curPos] ? 'R' : 'W');

        // R変換チェック
        if (curPos >= K && !isRed[curPos] && c == 'R')
        {
            if (rProb > 0 && rng() % rProb == 0)
            {
                moves.push_back(-1);
                isRed[curPos] = 1;
            }
        }
    }

    // 配達先への最短経路
    while (curPos != targetShop)
    {
        int next = -1;
        for (int v : adj[curPos])
        {
            if (dist[v][targetShop] < dist[curPos][targetShop])
            {
                next = v;
                break;
            }
        }
        if (next == -1)
            return {{}, false};
        moves.push_back(next);
        curPos = next;

        // 途中で店に入ったら失敗
        if (curPos < K && curPos != targetShop)
        {
            return {{}, false};
        }
    }

    return {moves, true};
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

    // 距離計算
    calcDist();

    // 配達予約システム
    vector<char> isRed(N, 0);
    vector<set<string>> shopInventory(K);
    int curPos = 0;
    int usedSteps = 0;
    int score = 0;
    vector<int> allMoves;
    string currentCone;

    mt19937 rng(12345);
    int rProb = 50;

    // パターン候補（長さ1-4）
    vector<string> patternCandidates;
    for (int len = 1; len <= 4; len++)
    {
        for (int mask = 0; mask < (1 << len); mask++)
        {
            string pattern;
            for (int i = 0; i < len; i++)
            {
                pattern += (mask & (1 << i)) ? 'R' : 'W';
            }
            patternCandidates.push_back(pattern);
        }
    }

    // 近い店から順に処理
    vector<pair<int, int>> shopDist;
    for (int i = 0; i < K; i++)
    {
        shopDist.push_back({dist[0][i], i});
    }
    sort(shopDist.begin(), shopDist.end());

    for (auto [d, shop] : shopDist)
    {
        if (usedSteps >= T - 300)
            break;

        // この店に配達可能なパターンを試す
        for (const string &pattern : patternCandidates)
        {
            if (shopInventory[shop].count(pattern))
                continue;
            if (usedSteps >= T - 200)
                break;

            int tmpPos = curPos;
            vector<char> tmpIsRed = isRed;
            auto [moves, success] = createAndDeliver(tmpPos, pattern, shop, tmpIsRed, currentCone, rng, rProb);

            if (success && currentCone == pattern && usedSteps + moves.size() < T - 100)
            {
                // 適用
                curPos = tmpPos;
                isRed = tmpIsRed;
                for (int m : moves)
                    allMoves.push_back(m);
                usedSteps += moves.size();
                shopInventory[shop].insert(pattern);
                score++;
            }
        }
    }

    cerr << "Score: " << score << "\n";

    for (int m : allMoves)
    {
        if (m == -1)
        {
            cout << "-1\n";
        }
        else
        {
            cout << m << "\n";
        }
    }

    return 0;
}

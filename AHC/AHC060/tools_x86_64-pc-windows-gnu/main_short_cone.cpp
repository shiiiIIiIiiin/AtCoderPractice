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

// 最短経路で移動
vector<int> moveToTarget(int from, int to)
{
    vector<int> moves;
    int cur = from;
    while (cur != to)
    {
        int next = -1;
        for (int v : adj[cur])
        {
            if (dist[v][to] < dist[cur][to])
            {
                next = v;
                break;
            }
        }
        if (next == -1)
            break;
        moves.push_back(next);
        cur = next;
    }
    return moves;
}

// 短いコーンを作成して配達
vector<int> makeAndDeliver(int curPos, int coneLen, int targetShop,
                           vector<char> &isRed, mt19937 &rng, int rProb)
{
    vector<int> moves;

    // 各色の木から1つずつ選ぶ（単純にランダム）
    vector<int> wTrees, rTrees;
    for (int i = K; i < N; i++)
    {
        if (isRed[i])
            rTrees.push_back(i);
        else
            wTrees.push_back(i);
    }

    // coneLen個のアイスを集める
    for (int j = 0; j < coneLen; j++)
    {
        int nextTree;
        if (rng() % 2 == 0 && !wTrees.empty())
        {
            nextTree = wTrees[rng() % wTrees.size()];
        }
        else if (!rTrees.empty())
        {
            nextTree = rTrees[rng() % rTrees.size()];
        }
        else if (!wTrees.empty())
        {
            nextTree = wTrees[rng() % wTrees.size()];
        }
        else
        {
            break;
        }

        // 木へ移動
        auto treeMoves = moveToTarget(curPos, nextTree);
        for (int m : treeMoves)
            moves.push_back(m);
        curPos = nextTree;

        // R変換チェック
        if (!isRed[curPos] && rng() % rProb == 0)
        {
            moves.push_back(-1);
            isRed[curPos] = 1;
        }
    }

    // 店へ移動して配達
    auto shopMoves = moveToTarget(curPos, targetShop);
    for (int m : shopMoves)
        moves.push_back(m);

    return moves;
}

struct Params
{
    int coneLen; // コーンの長さ(2-4)
    int rProb;   // R変換確率
};

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

    // 店の訪問順序を最適化（近傍探索）
    vector<int> shopOrder;
    vector<bool> visited(K, false);
    int curShop = 0;
    visited[0] = true;
    shopOrder.push_back(0);

    for (int i = 1; i < K; i++)
    {
        int nearest = -1;
        int minDist = 1e9;
        for (int j = 0; j < K; j++)
        {
            if (!visited[j] && dist[curShop][j] < minDist)
            {
                minDist = dist[curShop][j];
                nearest = j;
            }
        }
        visited[nearest] = true;
        shopOrder.push_back(nearest);
        curShop = nearest;
    }

    // 焼きなまし法でパラメータを最適化
    mt19937 rng(42);
    uniform_real_distribution<double> uni(0.0, 1.0);

    Params best{3, 50};
    int bestScore = 0;
    Params cur = best;

    const double timeLimitSec = 1.5;
    const auto start = chrono::high_resolution_clock::now();

    while (true)
    {
        const auto now = chrono::high_resolution_clock::now();
        double elapsed = chrono::duration<double>(now - start).count();
        if (elapsed >= timeLimitSec)
            break;

        // シミュレーション
        vector<char> isRed(N, 0);
        vector<set<string>> shopInventory(K);
        int curPos = 0;
        int usedSteps = 0;
        int score = 0;

        for (int shop : shopOrder)
        {
            if (usedSteps + dist[curPos][shop] + cur.coneLen + 10 > T - 50)
                break;

            // 店へ移動
            auto moves = moveToTarget(curPos, shop);
            usedSteps += moves.size();
            curPos = shop;

            // コーンを作成して配達
            string cone;
            for (int j = 0; j < cur.coneLen; j++)
            {
                int nextTree = (K + rng() % (N - K));
                moves = moveToTarget(curPos, nextTree);
                usedSteps += moves.size();
                curPos = nextTree;

                // R変換
                if (!isRed[curPos] && rng() % cur.rProb == 0)
                {
                    isRed[curPos] = 1;
                    usedSteps++;
                }

                cone += (isRed[curPos] ? 'R' : 'W');
            }

            // 配達
            moves = moveToTarget(curPos, shop);
            usedSteps += moves.size();
            curPos = shop;

            if (!shopInventory[shop].count(cone))
            {
                shopInventory[shop].insert(cone);
                score++;
            }
        }

        // 焼きなまし採択判定
        if (score > bestScore)
        {
            bestScore = score;
            best = cur;
        }

        // パラメータを変更
        Params nxt = cur;
        if (rng() % 2 == 0)
        {
            nxt.coneLen = max(2, min(4, cur.coneLen + (rng() % 2 == 0 ? -1 : 1)));
        }
        else
        {
            nxt.rProb = max(20, min(100, cur.rProb + (rng() % 2 == 0 ? -5 : 5)));
        }
        cur = nxt;
    }

    // 最終実行
    vector<char> isRed(N, 0);
    vector<set<string>> shopInventory(K);
    int curPos = 0;
    int usedSteps = 0;
    int totalScore = 0;
    vector<int> allMoves;

    for (int shop : shopOrder)
    {
        if (usedSteps + dist[curPos][shop] + best.coneLen + 20 > T - 50)
            break;

        // 店へ移動
        auto moves = moveToTarget(curPos, shop);
        for (int m : moves)
            allMoves.push_back(m);
        usedSteps += moves.size();
        curPos = shop;

        // コーンを作成して配達
        string cone;
        for (int j = 0; j < best.coneLen; j++)
        {
            int nextTree = (K + rng() % (N - K));
            moves = moveToTarget(curPos, nextTree);
            for (int m : moves)
                allMoves.push_back(m);
            usedSteps += moves.size();
            curPos = nextTree;

            // R変換
            if (!isRed[curPos] && rng() % best.rProb == 0)
            {
                allMoves.push_back(-1);
                isRed[curPos] = 1;
                usedSteps++;
            }

            cone += (isRed[curPos] ? 'R' : 'W');
        }

        // 配達
        moves = moveToTarget(curPos, shop);
        for (int m : moves)
            allMoves.push_back(m);
        usedSteps += moves.size();
        curPos = shop;

        if (!shopInventory[shop].count(cone))
        {
            shopInventory[shop].insert(cone);
            totalScore++;
        }
    }

    cerr << "Score: " << totalScore << "\n";

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

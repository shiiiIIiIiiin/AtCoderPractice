#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using ll = long long;

const ll MOD = 998244353;
const ll MOD2 = 1'000'000'007;

long long modinv(long long a, long long m) {
    long long b = m, u = 1, v = 0;
    while (b) {
        long long t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    u %= m; if (u < 0) u += m;
    return u;
}

long long modpow(long long a, long long n, long long mod) {
    long long res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

ll dx[] = { 1, 0, -1, 0 }, dy[] = { 0, 1, 0, -1 };
const ll INF = LLONG_MAX / 2;

//cin.tie(nullptr);
//ios::sync_with_stdio(false);

struct edge {
    int c, x, y;
    bool operator>(const edge& other)const {
        return c > other.c;
    }
};

bool dfs(vector<vector<pair<int, int>>>& G, vector<vector<int>>& A, int start, int pos, vector<bool>& visited, int cost) {
    bool res = true;

    //まず自分自身の評価
    if (A[start][pos] != cost)return false;

    //次に自分につながったものの評価
    //つながってるもので一つでも違反があるものがあればfalseにする
    for (int i = 0; i < G[pos].size(); i++) {
        auto [nex, c] = G[pos][i];
        if (visited[nex])continue;
        visited[nex] = true;

        if (!dfs(G, A, start, nex, visited, cost + c))res = false;
    }

    return res;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    //辺の重みが小さい順に採用していくのがいい
    //そうじゃない場合、「他の辺を通って（遠回りして）たどり着くようなパス」があるはずだが、これは最小性に違反する
    int N; cin >> N;

    priority_queue<edge, vector<edge>, greater<edge>> pq;
    vector<vector<int>> A(N + 1, vector<int>(N + 1));


    for (int i = 1; i < N; i++)for (int j = i + 1; j <= N; j++) {
        cin >> A[i][j];
        A[j][i] = A[i][j];
        edge e = { A[i][j],i,j };
        pq.push(e);
    }

    vector<vector<pair<int,int>>> G(N + 1);
    vector<vector<bool>> used(N + 1, vector<bool>(N + 1, false));
    dsu uf(N + 1);

    while (!pq.empty()) {
        edge e = pq.top(); pq.pop();
        int c = e.c, x = e.x, y = e.y;

        if (uf.same(x, y))continue;//連結なら一旦見なくていい

        uf.merge(x, y);//連結にさせる
        G[x].push_back({ y,c });
        G[y].push_back({ x,c });
    }

    //正当性を判断するBFSをする
    
    for (int i = 1; i <= N; i++) {
        vector<bool> visited(N + 1);
        visited[i] = true;
        if (!dfs(G, A, i, i, visited, 0)) {//違反してたら
            cout << "No" << endl;
            return 0;
        }
    }

    cout << "Yes" << endl;
}
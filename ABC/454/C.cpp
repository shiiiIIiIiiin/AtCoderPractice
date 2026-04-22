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


void dfs(int pos, vector<bool>& visited, vector<vector<int>>& G) {
    visited[pos] = true;

    for (int i = 0; i < G[pos].size(); i++) {
        int nex = G[pos][i];
        if (visited[nex])continue;

        dfs(nex, visited, G);
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    
    vector<vector<int>> G(N + 1);

    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        G[a].push_back(b);
    }

    vector<bool> visited(N + 1);
    
    dfs(1, visited, G);

    int ans = 0;
    for (int i = 1; i <= N; i++)if (visited[i])ans++;

    cout << ans << endl;
}
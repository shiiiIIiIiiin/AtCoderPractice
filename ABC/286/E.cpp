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

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    //O(N^3)かけて全部BFSしちゃえばいいのでは？

    int N; cin >> N;
    vector<ll> A(N);
    for (int i = 0; i < N; i++)cin >> A[i];

    vector<string> S(N);
    for (int i = 0; i < N; i++)cin >> S[i];

    int Q; cin >> Q;

    //前計算、ワーシャルフロイドする
    vector<vector<pair<ll, ll>>> dp(N, vector<pair<ll, ll>>(N, { INF,-INF / 400 }));

    for (int i = 0; i < N; i++)for (int j = 0; j < N; j++) {
        if (S[i][j] == 'Y')dp[i][j] = { 1,A[i] + A[j] };
        else if (i == j)dp[i][i] = { 0,A[i] };
    }

    for (int k = 0; k < N; k++)for (int i = 0; i < N; i++)for (int j = 0; j < N; j++) {
        //dp[i][j] = min(dp[i][k] + dp[k][j], dp[i][j]);
        ll nex_dist = dp[i][k].first + dp[k][j].first;
        ll nex_val = dp[i][k].second + dp[k][j].second - A[k];//kを２回数えるのを防止

        if (nex_dist < dp[i][j].first) {
            dp[i][j] = { nex_dist,nex_val };
        }
        else if (nex_dist == dp[i][j].first) {
            dp[i][j].second = max(dp[i][j].second, nex_val);
        }
    }

    for (; Q--;) {
        int u, v; cin >> u >> v;
        u--, v--;

        if (dp[u][v].first > INF / 500)cout << "Impossible" << endl;
        else cout << dp[u][v].first << " " << dp[u][v].second << endl;
    }

}
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

    ll N, M; cin >> N >> M;
    vector<vector<ll>> dp(2, vector<ll>(N));

    /*
    dp[0][n]:=n人目までルール通りに決めたとき、n人目が1人目と同じ数を持っている場合の数
    dp[1][n]:=n人目までルール通りに決めたとき、n人目が1人目と異なる数を持っている場合の数

    dp[0][n]=dp[1][n-1]
    dp[1][n]=dp[0][n-1]+(M-2)dp[1][n-1]
    */

    dp[0][0] = M;
    dp[1][0] = 0;

    for (int n = 1; n < N; n++) {
        dp[0][n] = dp[1][n - 1];
        dp[1][n] = (M - 1) * dp[0][n - 1] + (M - 2) * dp[1][n - 1];

        dp[1][n] %= MOD;
    }

    cout << dp[1][N - 1] << endl;
}
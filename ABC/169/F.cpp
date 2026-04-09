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

    //dp[n][s]:=n個目まで決めたとき、合計がsになる個数

    vector<vector<ll>> dp(3010, vector<ll>(3010, 0));
    dp[0][0] = 1;

    ll N, S; cin >> N >> S;
    vector<ll> A(N + 1);
    for (int i = 1; i <= N; i++)cin >> A[i];

    for (int n = 1; n <= N; n++) {
        for (int s = 0; s <= S; s++) {
            dp[n][s] = 2 * dp[n - 1][s];
            if (s - A[n] >= 0)dp[n][s] += dp[n - 1][s - A[n]];
            dp[n][s] %= MOD;
        }
    }

    cout << dp[N][S] << endl;
}
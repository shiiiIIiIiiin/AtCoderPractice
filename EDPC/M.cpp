//#define _GLIBCXX_DEBUG

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

    int N, K; cin >> N >> K;
    //dp[n][k]:=n人目まででｋ個配る方法
    vector<vector<ll>> dp(N + 1, vector<ll>(K + 1, 0));
    dp[0][0] = 1;

    vector<ll> A(N + 1);
    for (int i = 1; i <= N; i++)cin >> A[i];

    for (int n = 1; n <= N; n++) {
        //dp[n-1]の累積和を取る
        for (int i = 1; i <= K; i++)dp[n - 1][i] += dp[n - 1][i - 1];

        for (int k = 0; k <= K; k++) {
            /*
            for (int i = 0; i <= A[n]; i++) {
                if (k - i < 0)continue;
                dp[n][k] += dp[n - 1][k - i];
                dp[n][k] %= MOD2;
            }
　　　　　　*/

            dp[n][k] = dp[n - 1][k] - (k - A[n] - 1 < 0 ? 0 : dp[n - 1][k - A[n] - 1]);
            dp[n][k] %= MOD2;
        }
    }

    cout << dp[N][K] << endl;

}
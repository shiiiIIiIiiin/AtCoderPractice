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

    //区間dpをする？
    int N; cin >> N;
    vector<int> P(N + 2, 0), A(N + 2, 0);
    for (int i = 1; i <= N; i++)cin >> P[i] >> A[i];

    vector<vector<ll>> dp(N + 1, vector<ll>(N + 2, 0));
    //dp[l][r]:=[l,r]の区間を残した状態で得られる最大の得点

    /*
    幅の大きい順に求めることができる
　　dp[l][r]=max(dp[l-1][r]+A[l-1],dp[l][r+1]+A[r+1])
    */

    dp[1][N] = 0;//width=Nの場合

    for (int width = N - 1; width >= 0; width--) {
        for (int l = 1; l + width <= N; l++) {
            int r = l + width;
            dp[l][r] = max(dp[l - 1][r] + (l <= P[l - 1] && P[l - 1] <= r ? A[l - 1] : 0), dp[l][r + 1] + (l <= P[r + 1] && P[r + 1] <= r ? A[r + 1] : 0));
        }
    }

    ll ans = -1;

    for (int i = 1; i <= N; i++)ans = max(ans, dp[i][i]);

    cout << ans << endl;

}
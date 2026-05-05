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


    /*
      自動テストしようと思ったら手が滑って提出しちゃった
      　and
      多分無理なので順表を見て驚かせるためにブラフで提出している







    */




    //--------------------------------------------------------------------------------------------------------


    /*
    連続する空きマス2つのうちどちらかはコストを払って休日にしないといけない
　　逆に、どの連続する２つもどちらともをコストを書ける必要はない
　　dpできる？？
    最小値は累積和にしておけばO(K)でいける？
    */

    int T; cin >> T;

    for (; T--;) {
        ll N, K; cin >> N >> K;
        vector<ll> A(N + 1);
        for (int i = 1; i <= N; i++)cin >> A[i];

        /*dp[0][n]:=n-1日目まで決めて、n-1日目が休日であるときの1日目からn日目までを全部休みにするのに必要なコストの最小値
          dp[1][n]:=n-1日目まで決めて、n-1日目が休日でないときの最小値
        */

        vector<vector<ll>> dp(2, vector<ll>(N + 1, INF));
        dp[0][0] = 0;
        dp[1][0] = 0;

        for (int n = 1; n <= N; n++) {
            dp[0][n] = min(dp[0][n - 1] + A[n], dp[1][n - 1] + A[n]);
            dp[1][n] = dp[0][n - 1];
        }

        ll ans = INF;

        for (int i = 1; i <= N; i++)dp[0][i] += dp[0][i - 1];

        for (int i = 0; i + K <= N; i++) {
            //ans = min(ans, sum_dp[i + K] - sum_dp[i]);　みたいなことしたらいい感じにならない？
            ans = min(ans, dp[0][i + K] - dp[0][i]);
        }

        cout << ans << endl;

    }

}
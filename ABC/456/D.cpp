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

    string S; cin >> S;
    int N = S.size();
    vector<vector<ll>> dp(3, vector<ll>(N + 1, 0));

    //dp[i][n]:=文字'a'+iを最後に使ったもので,n-1文字目までで、次n文字目の文字でおわる

    /*
    dp[0][n]=dp[0][n-1]+dp[1][n-1]+dp[2][n-1]

    */
    
    for (int n = 1; n <= N; n++) {
        
        if (S[n - 1] == 'a') {
            dp[0][n] = dp[0][n - 1] + dp[1][n - 1] + dp[2][n - 1] + 1;
            dp[1][n] = dp[1][n - 1];
            dp[2][n] = dp[2][n - 1];
        }
        else if (S[n - 1] == 'b') {
            dp[1][n] = dp[0][n - 1] + dp[1][n - 1] + dp[2][n - 1] + 1;
            dp[0][n] = dp[0][n - 1];
            dp[2][n] = dp[2][n - 1];
        }
        else {
            dp[2][n] = dp[0][n - 1] + dp[1][n - 1] + dp[2][n - 1] + 1;
            dp[1][n] = dp[1][n - 1];
            dp[0][n] = dp[0][n - 1];
        }

        dp[0][n] %= MOD;
        dp[1][n] %= MOD;
        dp[2][n] %= MOD;
    }

    cout << (dp[0][N] + dp[1][N] + dp[2][N]) % MOD << endl;
}
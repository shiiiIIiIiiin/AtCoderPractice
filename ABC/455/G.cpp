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
    vector<vector<bool>> is_cycle(N + 1, vector<bool>(N + 1, false));
    vector<int> dp(N + 1);
    dp[0] = -1;

    for (int width = 1; width <= N; width++) {
        for (int l = 0; l + width - 1 < N; l++) {
            int r = l + width - 1;

            if (width == 1) {
                is_cycle[l][r] = true;
                continue;
            }
            else if (width == 2) {
                is_cycle[l][r] = S[l] == S[r];
                continue;
            }

            is_cycle[l][r] = S[l] == S[r] && is_cycle[l + 1][r - 1];
        }
    }

    for (int i = 1; i <= N; i++) {
        dp[i] = dp[i - 1] + 1;
        for (int len = 1; len <= i; len++) {
            if (is_cycle[i - len][i - 1])dp[i] = min(dp[i], dp[i - len] + 1);
        }
    }

    cout << dp[N] << endl;

}
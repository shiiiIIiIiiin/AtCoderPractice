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
const ll INF = LLONG_MAX / 3;

vector<ll> sum;

ll solve(int l, int r, vector<ll>& A, vector<vector<ll>>& dp) {
    if (dp[l][r] != INF)return dp[l][r];
    if (l + 1 == r)return dp[l][r] = 0;

    ll res = INF;

    for (int m = l + 1; m < r; m++) {
        res = min(res, solve(l, m, A, dp) + solve(m, r, A, dp) + sum[r] - sum[l]);
    }

    return dp[l][r] = res;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    vector<ll> A(N);
    for (int i = 0; i < N; i++)cin >> A[i];
    sum.resize(N + 1, 0);
    for (int i = 1; i <= N; i++)sum[i] = sum[i - 1] + A[i - 1];

    vector<vector<ll>> dp(N + 1, vector<ll>(N + 1, INF));

    cout << solve(0, N, A, dp) << endl;
}
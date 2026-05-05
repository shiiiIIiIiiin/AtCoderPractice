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

using mint = modint998244353;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int n, m; cin >> n >> m;
    mint N = n, M = m;

    vector<vector<ll>> A(n, vector<ll>(m));
    for (int i = 0; i < n; i++)for (int j = 0; j < m; j++)cin >> A[i][j];

    vector<vector<ll>> cnt(n, vector<ll>(n * m + 1));
    for (int i = 0; i < n; i++)for (int j = 0; j < m; j++)cnt[i][A[i][j]]++;

    mint ans = 0;
    ll Mn = modpow(m, n, MOD);

    for (ll k = 0; k <= n * m; k++) {
        mint c = 1;

        for (int i = 0; i < n; i++)c *= M - cnt[i][k];
        ans += Mn - c;
    }

    cout << ans.val() << endl;
}
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

ll solve(ll l, ll r) {
    ll n = r - l + 1;
    if (r < l)return 0;
    return (n % MOD * (n % MOD + 1)) % MOD * modinv(2LL, MOD);
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    /*
    桁数別に考えればいい
    */

    ll N; cin >> N;
    string s = to_string(N);
    ll ans = 0;

    for (int d = 1; d <= s.size(); d++) {
        ans += solve(modpow(10LL, d - 1, INF), min(modpow(10LL, d, INF) - 1, N));
        ans %= MOD;
    }

    cout << ans << endl;
}
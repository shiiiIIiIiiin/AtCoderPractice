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

vector<ll> nnn(2e6 + 10, 1);

ll nCr(ll n, ll r) {
    if (n < r)return 0;
    return ((nnn[n] * modinv(nnn[n - r], MOD)) % MOD *modinv(nnn[r], MOD)) % MOD;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    ll N, M, S; cin >> N >> M >> S;

    for (ll i = 1; i < nnn.size(); i++) {
        nnn[i] = nnn[i - 1] * i;
        nnn[i] %= MOD;
    }

    ll ans = 0;

    for (ll i = 0; i <= S; i++) {
        if ((S - i) % (M + 1) != 0)continue;
        ans += nCr(i + N - 1, N - 1) * nCr(N, (S - i) / (M + 1)) * (((S - i) / (M + 1)) % 2 == 0 ? 1 : -1);
        ans += MOD;
        ans %= MOD;
    }

    cout << ans << endl;

}
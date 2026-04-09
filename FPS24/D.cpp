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

// 逆元階乗を前計算する
vector<ll> nnn(2e6 + 10, 1), inn(2e6 + 10, 1);

void precompute() {
    for (int i = 1; i < nnn.size(); i++) nnn[i] = (nnn[i - 1] * i) % MOD;
    inn[nnn.size() - 1] = modpow(nnn.back(), MOD - 2, MOD); // フェルマーの小定理
    for (int i = nnn.size() - 2; i >= 0; i--) inn[i] = (inn[i + 1] * (i + 1)) % MOD;
}

ll nCr(ll n, ll r) {
    if (r < 0 || n < r) return 0;
    return (((nnn[n] * inn[r]) % MOD) * inn[n - r]) % MOD;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    precompute();

    ll N, M; cin >> N >> M;

    if (N == 1) {
        cout << M + 1 << endl;
        return 0;
    }

    ll ans = 0;

    for (ll i = 0; i <= M - N + 1; i++) {
        ans += nCr(i + N, N) * nCr(M - i - 1, N - 2) * ((M + N + 1 - i) % 2 == 0 ? 1 : -1);
        ans += MOD;
        ans %= MOD;
    }

    ans *= nnn[N];
    ans %= MOD;
    cout << ans << endl;
}
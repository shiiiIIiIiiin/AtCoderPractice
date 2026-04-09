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

    string S, T; cin >> S >> T;
    int N = S.size(), M = T.size();
    vector<mint> s1(N), t1(M), s0(N), t0(M);

    for (int i = 0; i < N; i++) {
        s1[i] = S[i] == '1';
        s0[i] = S[i] == '0';
    }

    for (int i = 0; i < M; i++) {
        t1[i] = T[M - 1 - i] == '1';
        t0[i] = T[M - 1 - i] == '0';
    }

    vector<mint> res1 = convolution(s1, t1), res0 = convolution(s0, t0);
    ll ans = 1e7;
    for (int i = 0; i + M <= N; i++) {
        ans = min(ans, (ll)(M - res1[i + M - 1].val() - res0[i + M - 1].val()));
    }

    cout << ans << endl;

}
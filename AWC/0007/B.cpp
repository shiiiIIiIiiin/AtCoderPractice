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
    int N, K; cin >> N >> K;
    vector<set<string>> st(N);

    for (int i = 0; i < N; i++) {
        int M; cin >> M;
        for (int j = 0; j < M; j++) {
            string w; cin >> w;
            st[i].insert(w);
        }
    }

    ll ans = 0;

    for (int x = 0; x < N; x++)for (int y = x + 1; y < N; y++) {
        int cnt = 0;
        for (auto s : st[x])if (st[y].count(s))cnt++;
        ans += cnt >= K;
    }

    cout << ans << endl;

}
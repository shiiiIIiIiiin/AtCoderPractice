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

class UnionFind {
public:
    vector<ll> siz, par;
    UnionFind(ll n) {
        siz.assign(n, 1);
        par.assign(n, -1);
    }
    ll root(ll x) {
        return par[x] == -1 ? x : par[x] = root(par[x]);
    }
    void unite(ll x, ll y) {
        ll rx = root(x), ry = root(y);
        if (rx == ry) return;
        if (siz[rx] < siz[ry]) {
            par[rx] = ry;
            siz[ry] += siz[rx];
        }
        else {
            par[ry] = rx;
            siz[rx] += siz[ry];
        }
    }
    bool same(ll x, ll y) {
        return root(x) == root(y);
    }
};

ll dx[] = { 1, 0, -1, 0 }, dy[] = { 0, 1, 0, -1 };
const ll INF = LLONG_MAX / 2;

int main() {
    //コストが大きい順にくっつけるかを見ていく
    //くっつけるかの判定はくっつけることでグループ数が1にならないかどうか

    using mint = modint998244353;

    int N, M; cin >> N >> M;
    vector<int> U(M + 1), V(M + 1);
    for (int i = 1; i <= M; i++)cin >> U[i] >> V[i];

    vector<mint> cost(M + 1);
    
    mint ans = 0;
    for (int i = 1; i <= M; i++) {
        cost[i] = mint(2).pow(i);
        ans += cost[i];
    }

    int group_cnt = N;

    dsu uf(N + 1);

    for (int i = M; i >= 1; i--) {
        int u = U[i], v = V[i];
        mint c = cost[i];

        if (uf.same(u, v)) {
            ans -= c;
        }
        else {
            if (group_cnt - 1 >= 2) {
                uf.merge(u, v);
                ans -= c;
                group_cnt--;
            }
        }
    }

    cout << ans.val() << endl;
}
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

struct S {
    mint sum1, sum2;
    ll siz;
};

struct F {
    mint add;
};

S op(S a, S b) {
    return { a.sum1 + b.sum1,a.sum2 + b.sum2,a.siz + b.siz };
}

S e() {
    return { 0,0,0 };
}

S mapping(F f, S x) {
    if (f.add == 0)return x;
    return{ x.sum1 + f.add * x.siz,x.sum2 + x.sum1 * f.add * 2 + f.add.pow(2) * x.siz,x.siz };
}

F composition(F f, F g) {
    return { f.add + g.add };
}

F id() {
    return { 0 };
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int N, Q; cin >> N >> Q;

    vector<S> init(N, { 0,0,1 });
    lazy_segtree<S, op, e, F, mapping, composition, id> sg(init);

    for (; Q--;) {
        ll l, r, a; cin >> l >> r >> a;
        l--;

        sg.apply(l, r, { a });
        S res = sg.prod(l, r);

        mint ans = (res.sum1.pow(2) - res.sum2) * mint(2).inv();

        cout << ans.val() << endl;
    }
}
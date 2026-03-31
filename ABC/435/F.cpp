//#define _GLIBCXX_DEBUG

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <map>
#include <set>
#include <iterator>
#include <unordered_map>
#include <stack>
#include <string>
#include <cmath>
#include <iomanip>
#include <deque>
#include <unordered_set>
#include <locale>
#include <random>

using namespace std;
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


struct Node {
    ll val;
    int idx;
};

class SegTree {
public:
    vector<Node> dat;
    ll siz = 1;

    SegTree(ll n) {
        while (siz < n) siz *= 2;
        dat.resize(2 * siz, { -LLONG_MAX, -1 });
    }

    void update(int id, ll x) {
        int target = id + siz;
        dat[target] = { x, id };
        while (target > 1) {
            target /= 2;
            if (dat[2 * target].val >= dat[2 * target + 1].val) {
                dat[target] = dat[2 * target];
            }
            else {
                dat[target] = dat[2 * target + 1];
            }
        }
    }

    Node getmax_query(int L, int R, int a, int b, int u) {
        if (b <= L || R <= a) return { -LLONG_MAX, -1 };
        if (L <= a && b <= R) return dat[u];
        int m = (a + b) / 2;
        Node nl = getmax_query(L, R, a, m, 2 * u);
        Node nr = getmax_query(L, R, m, b, 2 * u + 1);
        return (nl.val >= nr.val) ? nl : nr;
    }

    Node getmax(int L, int R) {
        return getmax_query(L, R, 0, siz, 1);
    }
};

int dx[] = { 1, 0, -1, 0 }, dy[] = { 0, 1, 0, -1 };

const ll INF = LLONG_MAX / 2;

//cin.tie(nullptr);
//ios::sync_with_stdio(false);

ll solve(int L, int R, int pos, SegTree& sg) {
    if (R - L <= 1)return 0;//ベースケース

    ll res = 0;

    if (L < pos) {
        Node ML = sg.getmax(L, pos);
        res = max(res, solve(L, pos, ML.idx, sg) + abs(pos - ML.idx));
    }

    if (pos + 1 < R) {
        Node MR = sg.getmax(pos + 1, R);
        res = max(res, solve(pos + 1, R, MR.idx, sg) + abs(pos - MR.idx));
    }

    return res;
}

int main() {
    int N; cin >> N;
    vector<int> P(N);
    for (int i = 0; i < N; i++)cin >> P[i];

    int start = -1;
    for (int i = 0; i < N; i++)if (P[i] == N)start = i;

    SegTree sg(N);
    for (int i = 0; i < N; i++)sg.update(i, P[i]);

    cout << solve(0, N, start, sg) << endl;
}
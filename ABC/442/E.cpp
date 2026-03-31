//写経

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

int dx[] = { 1, 0, -1, 0 }, dy[] = { 0, 1, 0, -1 };

const ll INF = LLONG_MAX / 2;

//cin.tie(nullptr);
//ios::sync_with_stdio(false);

struct point {
    ll x, y;
};

ll cross(const point& a, const point& b) {
    return a.x * b.y - a.y * b.x;
}

bool cmp(const point& a, const point& b) {
    bool ah = a.y < 0 || (a.y == 0 && a.x < 0), bh = b.y < 0 || (b.y == 0 && b.x < 0);
    if (ah != bh)return ah < bh;
    return cross(a, b) > 0;

}

void argument_sort(vector<point>& points) {
    sort(points.begin(), points.end(), cmp);
}

int main() {
    int N, Q; cin >> N >> Q;
    vector<point> P(N);
    for (int i = 0; i < N; i++)cin >> P[i].x >> P[i].y;

    vector<ll> ord(N);
    for (int i = 0; i < N; i++)ord[i] = i;
    sort(ord.begin(), ord.end(), [&](int i, int j) {return cmp(P[i], P[j]); });
    reverse(ord.begin(), ord.end());

    vector<ll> rev(N);

    for(int i=0;i<N;i++){
        rev[ord[i]] = i;
    }

    vector<ll> l(N), r(N);
    l[0] = 0, r[N - 1] = N;
    for (int i = 1; i < N; i++) {
        l[i] = (cmp(P[ord[i]], P[ord[i - 1]]) ? i : l[i - 1]);
    }

    for (int i = N - 2; i >= 0; i--) {
        r[i] = (cmp(P[ord[i + 1]], P[ord[i]]) ? i + 1 : r[i + 1]);
    }

    for (; Q--;) {
        ll a, b; cin >> a >> b;
        a--, b--;
        a = l[rev[a]];
        b = r[rev[b]];

        if (a < b)cout << b - a << endl;
        else cout << N - a + b << endl;
    }
}
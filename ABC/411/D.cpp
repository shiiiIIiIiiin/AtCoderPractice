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

using namespace std;
using ll = long long;

const ll MOD = 998244353;
const ll MOD2 = 1'000'000'007;

class SegTree {
public:
    vector<ll> dat;
    ll siz = 1;

    SegTree(ll n) {
        while (siz < n) siz *= 2;
        dat.resize(2 * siz, -LLONG_MAX);
    }

    void update(int id, ll x) {
        id += siz;
        dat[id] = x;
        while (id != 0) {
            id /= 2;
            dat[id] = max(dat[2 * id], dat[2 * id + 1]);
        }
    }

    ll getval(int id) {
        return dat[id + siz];
    }

    ll getmax(ll L, ll R, ll a, ll b, ll u) {
        if (b <= L || R <= a) return -LLONG_MAX / 2;
        if (L <= a && b <= R) return dat[u];
        ll m = (a + b) / 2;
        return max(getmax(L, R, a, m, 2 * u),
            getmax(L, R, m, b, 2 * u + 1));
    }
};

class UnionFind {
public:
    vector<int> siz, par;
    UnionFind(int n) {
        siz.assign(n, 1);
        par.assign(n, -1);
    }
    int root(int x) {
        return par[x] == -1 ? x : par[x] = root(par[x]);
    }
    void unite(int x, int y) {
        int rx = root(x), ry = root(y);
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
    bool same(int x, int y) {
        return root(x) == root(y);
    }
};

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

int dx[] = { 1, 0, -1, 0 }, dy[] = { 0, 1, 0, -1 };

//ios::sync_with_stdio(false);
//cin.tie(nullptr);

int main() {
    int N, Q; cin >> N >> Q;
    vector<int> type(Q), p(Q);
    vector<string> s(Q);

    for (int id = 0; id < Q; id++) {
        
        cin >> type[id] >> p[id];
        if (type[id] == 2)cin >> s[id];
    }

    //最後にクエリ3が行われた時以降のものは無視していい

    
    //パソコンに対して行われる処理は、
    // ①③文字列を他のパソコンの文字列で入れ替えること、②文字列の追加

    vector<vector<string>> pc(N + 1);//サーバーをpc[0]とする

    int i = 0;
    vector<string> ans;

    for (int t = Q - 1; t >= 0; t--) {
        if (type[t] == 1) {
            if (i == p[t])i = 0;
        }
        else if (type[t] == 2) {
            if (i == p[t])ans.push_back(s[t]);
        }
        else {
            if (i == 0)i = p[t];
        }
    }

    for (int i = 0; i < ans.size(); i++)cout << ans[ans.size() - 1 - i];
}
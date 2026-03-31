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

int K = -1;
void dfs(int pos, int pre, vector<vector<pair<int,int>>>& G, int pre_col, vector<int>& col) {
    vector<int> nex_cols;
    for (int c = 1; c <= G[pos].size(); c++) {
        if (c != pre_col)nex_cols.push_back(c);
    }

    int cnt = -1;

    for (int i = 0; i < G[pos].size(); i++) {
        auto [nex, edge_id] = G[pos][i];
        if (nex == pre)continue;
        
        cnt++;
        col[edge_id] = nex_cols[cnt];
        dfs(nex, pos, G, nex_cols[cnt], col);
    }
}

int main() {
    int N; cin >> N;
    vector<vector<pair<int,int>>> G(N + 1);
    for (int i = 1; i <= N - 1; i++) {
        int a, b; cin >> a >> b;
        G[a].push_back({ b,i });
        G[b].push_back({ a,i });
    }

    for (int i = 1; i <= N; i++)K = max(K, int(G[i].size()));

    vector<int> col(N + 1, -1);
    dfs(1, -1, G, -1, col);

    cout << K << endl;
    for (int i = 1; i <= N - 1; i++)cout << col[i] << endl;
}
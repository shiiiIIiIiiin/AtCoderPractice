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

int H, W;

bool dfs(vector<string>& S, vector<vector<bool>>& visited, int px, int py) {
    visited[px][py] = true;

    bool res = true;

    if (px == 0 || px == H - 1 || py == 0 || py == W - 1)res = false;

    for (int d = 0; d < 4; d++) {
        int nx = px + dx[d], ny = py + dy[d];
        if (nx < 0 || H <= nx || ny < 0 || W <= ny)continue;
        if (visited[nx][ny])continue;
        if (S[nx][ny] == '#')continue;

        if (nx == 0 || nx == H - 1 || ny == 0 || ny == W - 1)res = false;
        if (!dfs(S, visited, nx, ny))res = false;
    }

    return res;
}

int main() {
    cin >> H >> W;
    vector<string> S(H);
    for (int i = 0; i < H; i++)cin >> S[i];

    int ans = 0;
    vector<vector<bool>> visited(H, vector<bool>(W));

    for (int i = 0; i < H; i++)for (int j = 0; j < W; j++) {
        if (visited[i][j])continue;
        if (S[i][j] == '#')continue;

        if (dfs(S, visited, i, j))ans++;
    }


    cout << ans << endl;
}
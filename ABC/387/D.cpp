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

int H, W;

int idx(int x, int y) {
    return x * W + y;
}


class Point {
public:
    int x, y, type, cost;

    Point(int _x, int _y, int _type, int _cost) {
        x = _x;
        y = _y;
        type = _type;
        cost = _cost;
    }
};

int main() {
    cin >> H >> W;
    vector<string> S(H);
    for (int i = 0; i < H; i++)cin >> S[i];

    //頂点倍化をすれば解ける？？

    vector<vector<bool>> visited(2, vector<bool>(H * W + 1, false));

    queue<Point> q;//頂点とコストを格納する
    
    int sx, sy, gx, gy;

    for (int i = 0; i < H; i++)for (int j = 0; j < W; j++) {
        if (S[i][j] == 'S') {
            sx = i, sy = j;
        }

        if (S[i][j] == 'G') {
            gx = i, gy = j;
        }
    }

    q.push(Point(sx, sy, 0, 0));
    q.push(Point(sx, sy, 1, 0));
    visited[0][idx(sx, sy)] = true;
    visited[1][idx(sx, sy)] = true;


    while (!q.empty()) {
        Point p = q.front(); q.pop();

        for (int i = 0; i < 4; i++) {

            int nx = p.x + dx[i], ny = p.y + dy[i], c = p.cost, t = p.type;

            if (t == 1 && i % 2 == 0)continue;
            if (t == 0 && i % 2 == 1)continue;

            if (nx < 0 || H <= nx || ny < 0 || W <= ny)continue;
            if (visited[t][idx(nx, ny)])continue;
            if (S[nx][ny] == '#')continue;

            if (S[nx][ny] == 'G') {
                cout << c + 1 << endl;
                return 0;
            }

            visited[t][idx(nx, ny)] = true;
            q.push({ Point(nx,ny,(t == 0 ? 1 : 0),c + 1) });
        }
    }

    cout << -1 << endl;
}
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

bool can_move(vector<pair<ll, ll>>& cur, int x, int y, vector<vector<ll>>& W, vector<vector<ll>>& D) {
    if (x == 0 && y == 0) return false;

    for (int i = 0; i < cur.size(); i++) {
        if (cur[i].second <= W[x][y] * (x + y))
            return false;
    }

    for (int i = 0; i < cur.size(); i++)
        cur[i].second -= W[x][y] * (x + y);

    return true;
}

bool checkQ(int& Q) {
    Q--;
    return Q == 0;
}

int main() {
    int N;
    cin >> N;
    vector<vector<ll>> W(N, vector<ll>(N)), D(N, vector<ll>(N));

    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) cin >> W[i][j];
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) cin >> D[i][j];

    int Q = 2 * N * N * N;
    vector<vector<bool>> moved(N, vector<bool>(N, false));

    
    for (int h = N; h >= 0; h--) {
        for (int w = N - 1; w >= 0; w--) {
            if (h < 0 || h >= N || w < 0 || w >= N) continue;
            if (h == 0 && w == 0) continue;
            if (moved[h][w]) continue;

            vector<pair<ll, ll>> cur;

            for (int i = 0; i < h; i++) {
                cout << "D" << endl;
                if (checkQ(Q)) return 0;
            }
            for (int i = 0; i < w; i++) {
                cout << "R" << endl;
                if (checkQ(Q)) return 0;
            }

            if (h != 0 || w != 0) {
                cout << 1 << endl;
                moved[h][w] = true;
                cur.push_back({ h * N + w, D[h][w] });
                if (checkQ(Q)) return 0;
            }

            for (int i = h; i > 0; i--) {
                cout << "U" << endl;
                if (checkQ(Q)) return 0;

                int x = i - 1, y = w;
                if (x == 0 && y == 0) continue;

                if (moved[x][y]) continue;
                if (can_move(cur, x, y, W, D) && !moved[x][y]) {
                    cout << 1 << endl;
                    cur.push_back({ x * N + y, D[x][y] });
                    moved[x][y] = true;
                    if (checkQ(Q)) return 0;
                }
            }

            for (int i = w; i > 0; i--) {
                cout << "L" << endl;
                if (checkQ(Q)) return 0;

                int x = 0, y = i - 1;
                if (x == 0 && y == 0) continue;

                if (moved[x][y]) continue;
                if (can_move(cur, x, y, W, D) && !moved[x][y]) {
                    cout << 1 << endl;
                    cur.push_back({ x * N + y, D[x][y] });
                    moved[x][y] = true;
                    if (checkQ(Q)) return 0;
                }
            }
        }
    }
}


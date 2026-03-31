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


int main() {
    //n×m盤面の質問をすると、もう置けないならmin(n,m)という回答かえってくる
    //kより小さい値がかえって来たらその長方形領域内に置けるマスがあるということ

    //盤面は最大1e6マス、2^20より小さいから二分探索的なノリでいける

    int N; cin >> N;
    ll x1 = 1, y1 = 1, x2 = N, y2 = N;
    
    
    while (x1 != x2) {//まずx座標を特定する
        ll nex = (x1 + x2) / 2;
        cout << "? " << x1 << " " << nex << " " << y1 << " " << y2 << endl;
        int res; cin >> res;
        int k = nex - x1 + 1;

        if (res == k)x1 = nex + 1;
        else x2 = nex;
    }

    while (y1 != y2) {//次にy座標を特定する
        ll nex = (y1 + y2) / 2;
        cout << "? " << 1 << " " << N << " " << y1 << " " << nex << endl;

        int k = nex - y1 + 1, res;
        cin >> res;

        if (res == k) y1 = nex + 1;
        else y2 = nex;
    }
    
    cout << "! " << x1 << " " << y1 << endl;
}
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

double PI = 3.1415926535897;
int main() {
    cout << fixed << setprecision(10);
    double a, b, x; cin >> a >> b >> x;

    /*
    * まず、どういう状態でこぼれ始めるか調べる必要がある
    * 
    * x>a*a*b/2の時、パターン①でこぼれ始める
    * それ以外の時、　パターン②でこぼれ始める
    * 
    * ①高さ h は a*h*a/2 + x = baa　を満たし、h=2(x-baa)/(a*a) →　atan(h/a)=atan(2x/(a*a*a))
    * ②高さ h は hba/2 = x を満たし、h=2x/(ab) →　atan(b/h)=atan(abb/(2x))
    * 
    */

    if (2 * x > a * a * b)cout << 180 / PI * atan(2 * (b * a * a - x) / (a * a * a));
    else cout << 180 / PI * atan(a * b * b / (2 * x));
}
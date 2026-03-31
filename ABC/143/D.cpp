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
    int N; cin >> N;
    vector<ll> L(N);
    for (int i = 0; i < N; i++)cin >> L[i];

    sort(L.begin(), L.end());

    //三角形の成立条件は, a<=b<=cとして、c-b<aである
    ll ans = 0;
    for (int i = 0; i + 2 < N; i++) {
        for (int j = i + 1; j + 1 < N; j++) {
            //a,bを全探索
            //c<a+b
            ll a = L[i], b = L[j], s = a + b;

            //L[j+1]からL[N-1]の間でsより小さい値がいくつあるか
            
            ll l = j, r = N, m;

            while (r - l > 1) {
                m = (r + l) / 2;
                if (L[m] < s)l = m;
                else r = m;
            }

            ans += l - j;
        }
    }

    cout << ans << endl;
}
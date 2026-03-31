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
    ll N; cin >> N;
    vector<ll> A(N);
    for (int i = 0; i < N; i++)cin >> A[i];

    sort(A.begin(), A.end());

    /*
    ありうるのは
    ・全部一番大きいものの長さだった
    ・全部一番大きいものと小さいものの和だった
    の2通りのみ
    */

    ll c1 = A.back(), c2 = A[0] + A.back();

    bool f1 = true, f2 = true;

    if (N % 2 == 0) {
        for (int i = 0; i < N; i++) {
            if (A[N - 1 - i] + A[i] != c2)f2 = false;
        }
    }
    else {
        f2 = false;
    }

    int s = N - 1;
    while (s >= 0) {
        if (A[s] == c1) {
            A.pop_back();
            s--;
        }
        else break;
    }

    int n = A.size();

    if(n%2==0){
        for (int i = 0; i < n; i++) {
            if (A[i] + A[n - 1 - i] != c1)f1 = false;
        }
    }
    else {
        f1 = false;
    }

    if (f1)cout << c1 << " ";
    if (f2)cout << c2 << endl;
}
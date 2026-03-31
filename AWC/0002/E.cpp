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
    ll N, S; cin >> N >> S;
    vector<ll> A(N);
    for (int i = 0; i < N; i++)cin >> A[i];

    vector<ll> A1, A2;

    for (int i = 0; i < N; i++) {
        if (i < N / 2)A1.push_back(A[i]);
        else A2.push_back(A[i]);
    }

    vector<ll> sum1, sum2;

    int n = A1.size();
    for (int s = 0; s < (1 << n); s++) {
        ll sum = 0;
        for (int i = 0; i < n; i++)if ((s >> i) & 1)sum += A1[i];
        sum1.push_back(sum);
    }

    n = A2.size();
    for (int s = 0; s < (1 << n); s++) {
        ll sum = 0;
        for (int i = 0; i < n; i++)if ((s >> i) & 1)sum += A2[i];
        sum2.push_back(sum);
    }

    map<ll, ll> mp;
    for (int i = 0; i < sum2.size(); i++)mp[sum2[i]]++;

    ll ans = 0;

    for (int i = 0; i < sum1.size(); i++)if(mp.count(S-sum1[i]))ans += mp[S - sum1[i]];

    cout << ans << endl;
}
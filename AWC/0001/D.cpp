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
    ll N, M, K; cin >> N >> M >> K;
    vector<pair<ll, ll>> P(N + 1);
    for (int i = 1; i <= N; i++)cin >> P[i].first >> P[i].second;

    vector<vector<ll>> dp(N + 1, vector<ll>(M + 1, -INF));
    
    ll ans = 0;

    for (int i = 1; i <= N; i++) {
        auto [A, B] = P[i];

        for (int j = 0; j <= M; j++) {
            if (j - B < 0)continue;
            if (j == B) {
                dp[i][j] = A;
            }

            for (int k = 1; k <= K; k++) {
                if (i - k < 0)break;
                if (dp[i - k][j - B] >= 0)dp[i][j] = max(dp[i][j], dp[i - k][j - B] + A);
            }

            ans = max(ans, dp[i][j]);
        }
    }

    cout << ans << endl;
}
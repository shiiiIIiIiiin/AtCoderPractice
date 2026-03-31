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

class SegTree {
public:
    vector<ll> dat;
    ll siz = 1;

    SegTree(ll n) {
        while (siz < n) siz *= 2;
        dat.resize(2 * siz, -LLONG_MAX / 4);
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

    ll getmax_query(ll L, ll R, ll a, ll b, ll u) {
        if (b <= L || R <= a) return -LLONG_MAX / 2;
        if (L <= a && b <= R) return dat[u];
        ll m = (a + b) / 2;
        return max(getmax_query(L, R, a, m, 2 * u),
            getmax_query(L, R, m, b, 2 * u + 1));
    }

    ll getmax(ll L, ll R) {
        return getmax_query(L, R, 0, siz, 1);
    }
};

int dx[] = { 1, 0, -1, 0 }, dy[] = { 0, 1, 0, -1 };

const ll INF = LLONG_MAX / 2;

//cin.tie(nullptr);
//ios::sync_with_stdio(false);

int main() {
    ll W, N; cin >> W >> N;
    vector<ll> L(N + 1), R(N + 1), V(N + 1);
    for (int i = 1; i <= N; i++)cin >> L[i] >> R[i] >> V[i];

    //dp[n][w]:=料理nまで使って香辛料をw使うときにできる最大価値

    vector<vector<ll>> dp(N + 1, vector<ll>(W + 1, -INF));
    dp[0][0] = 0;

    SegTree sg(W + 1);
    sg.update(0, 0);

    for (int n = 1; n <= N; n++) {
        for (int w = 0; w <= W; w++) {
            /*
            * 
            dp[n][w] = max(dp[n-1][w-R[n]～w-L[n]]) + V[n],dp[n-1][w])
            */

            dp[n][w] = max(sg.getmax(max(0LL, w - R[n]), max(w - L[n] + 1, 0LL)) + V[n], dp[n - 1][w]);
        }

        for (int w = 0; w <= W; w++)sg.update(w, dp[n][w]);
    }

    cout << (dp[N][W] >= 0 ? dp[N][W] : -1) << endl;
}
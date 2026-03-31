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

int dx[] = { 1, 0, -1, 0 }, dy[] = { 0, 1, 0, -1 };

const ll INF = LLONG_MAX / 2;

//cin.tie(nullptr);
//ios::sync_with_stdio(false);

ll l(pair<ll, ll>& A, pair<ll, ll>& B) {
    return (A.first - B.first) * (A.first - B.first) + (A.second - B.second) * (A.second - B.second);
}

int main() {
    int N, K; cin >> N >> K;
    vector<pair<ll, ll>> P(N);
    for (int i = 0; i < N; i++)cin >> P[i].first >> P[i].second;

    vector<vector<ll>> dp(1 << N, vector<ll>(K + 1, INF));
    dp[0][0] = 0;
    vector<ll> d(1 << N, -1);

    for (int i = 0; i < 1 << N; i++) {
        vector<int> g;
        for (int j = 0; j < N; j++)if ((i >> j) & 1)g.push_back(j);

        int n = g.size();
        for (int s = 0; s < n; s++)for (int t = s + 1; t < n; t++) {
            d[i] = max(d[i], l(P[g[s]], P[g[t]]));
        }
    }

    for (int s = 1; s < 1 << N; s++) {
        for (int cnt = 1; cnt <= K; cnt++) {

            for (int sub = s; sub > 0; sub = (sub - 1) & s) {
                dp[s][cnt] = min(dp[s][cnt], max(dp[s - sub][cnt - 1], d[sub]));
            }
        }
    }

    cout << dp[(1 << N) - 1][K] << endl;
}
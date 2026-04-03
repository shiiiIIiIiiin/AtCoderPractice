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

int main() {
    int N; cin >> N;
    vector<ll> A(2 * N);
    for (int i = 0; i < 2 * N; i++)cin >> A[i];

    vector<vector<ll>> dp(2 * N + 1, vector<ll>(2 * N + 1, INF));
    //dp[l][r]:=[l,r)を取り除くのにかかる最小コスト

    for (int i = 0; i <= 2 * N; i++)dp[i][i] = 0;

    for (int len = 2; len <= 2 * N; len += 2) {
        //長さがlenの部分列を消滅させるのに必要な最小コストを全て求める
        for (int l = 0; l + len <= 2 * N; l++) {
            int r = l + len;

            dp[l][r] = min(dp[l][r], dp[l + 1][r - 1] + abs(A[l] - A[r - 1]));

            for (int k = l + 2; k < r; k += 2) {
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k][r]);
            }
        }
    }

    cout << dp[0][2 * N] << endl;
}
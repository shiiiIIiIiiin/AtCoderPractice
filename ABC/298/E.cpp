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

ll N, A, B, P, Q;

ll dp[110][110][2];

ll solve(ll a, ll b, int turn) {
    if (a == N)return 1;
    if (b == N)return 0;

    if (dp[a][b][turn] != -1)return dp[a][b][turn];

    ll sum_prob = 0;

    if (turn == 0) {
        for (int i = 1; i <= P; i++) {
            ll nex = min(N, a + i);
            sum_prob += solve(nex, b, 1);
        }

        sum_prob %= MOD;
        return dp[a][b][turn] = (sum_prob * modinv(P, MOD)) % MOD;
        
    }
    else {
        for (int i = 1; i <= Q; i++) {
            ll nex = min(N, b + i);
            sum_prob += solve(a, nex, 0);
        }

        sum_prob %= MOD;
        return dp[a][b][turn] = (sum_prob * modinv(Q, MOD)) % MOD;

    }
}

int main() {
    //計算量を気にせずに再帰で解く
    cin >> N >> A >> B >> P >> Q;

    for (int i = 0; i < 110; i++)for (int j = 0; j < 110; j++)for (int f = 0; f < 2; f++)dp[i][j][f] = -1;

    cout << solve(A, B, 0) << endl;

}
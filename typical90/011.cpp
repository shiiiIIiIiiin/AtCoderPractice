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

struct works {
    ll d, c, s;
};

int main() {
    int N; cin >> N;
    vector<works> P(N + 1);
    for (int i = 1; i <= N; i++)cin >> P[i].d >> P[i].c >> P[i].s;

    sort(P.begin(), P.end(), [](const works& a, const works& b) {
        return a.d < b.d;
        });

    /*
    DPする？
    
    dp[n][k]:=n番目までの仕事で、合計k日働いた時に得られる利益の最大値

    dp[n][k]=max( max(dp[n-1][k-C[n]])+S[n] ,   dp[n-1][k]   )
                 　↑働く(nの仕事をする）  ↑スルーする
    */

    int MAX_DAY = 5010;

    vector<vector<ll>> dp(N + 1, vector<ll>(MAX_DAY, -INF));
    dp[0][0] = 0;

    for (int n = 1; n <= N; n++) {
        auto [d, c, s] = P[n];
        for (int k = 0; k < MAX_DAY; k++) {
            //dp[n][k]を埋める

            //↓その仕事をやるだけの時間がない or 期限が過ぎてしまう時、スルーしかありえない
            if (k < c || d < k)dp[n][k] = dp[n - 1][k];
            else{
                dp[n][k] = max(dp[n - 1][k], dp[n - 1][k - c] + s);
            }
        }
    }

    ll ans = -1;

    for (int i = 0; i < MAX_DAY; i++)ans = max(ans, dp[N][i]);

    cout << ans << endl;
}
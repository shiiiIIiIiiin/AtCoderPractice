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
    ll N, M; cin >> N >> M;
    vector<ll> W(N), C(M);

    for (int i = 0; i < N; i++)cin >> W[i];
    for (int i = 0; i < M; i++)cin >> C[i];

    sort(C.rbegin(), C.rend());

    //bit全探索をする、典型90みたいな感じで

    vector<ll> memo(1 << N, 0);

    for (int s = 0; s < 1 << N; s++) {
        for (int i = 0; i < N; i++) {
            if ((s >> i) & 1)memo[s] += W[i];
        }
    }
    
    vector<ll> dp(1 << N, INF);
    dp[0] = 0;

    
    for (ll s = 0; s < (1 << N); s++) {
        if (dp[s] >= M)continue;

        ll nex = dp[s];
        ll c = C[nex];

        for (ll k = ((1 << N) - 1) & ~s; k > 0; k = (k - 1) & (((1 << N) - 1) & ~s)){
            if (memo[k] <= c) {
                dp[s | k] = min(dp[s | k], nex + 1);
            }
        }
    }

    if (dp[(1 << N) - 1] <= M)cout << "Yes";
    else cout << "No";
}
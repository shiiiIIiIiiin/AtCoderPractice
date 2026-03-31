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
    int N, K; cin >> N >> K;
    vector<ll> A(N);
    for (int i = 0; i < N; i++)cin >> A[i];
    sort(A.begin(), A.end());
    
    vector<ll> ans(K + 1, INF);
    ans[0] = 0;
    
    for (int k = 1; k <= K; k++) {
        //ans[k]を求める
        ll res = INF;
        for (int i = 0; i < N; i++) {
            ll a = A[i];
            // ans[id] + a > ans[k - 1]を満たす最小のidを求める
            ll l = -1, r = K + 1, m;
            while (r - l > 1) {
                m = (r + l) / 2;
                if (ans[m] + a > ans[k - 1])r = m;
                else l = m;
            }

            res = min(res, ans[r] + a);
        }

        ans[k] = res;
    }

    cout << ans[K] << endl;
}
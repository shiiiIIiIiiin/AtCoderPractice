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
    ll N, K, M; cin >> N >> K >> M;
    vector<ll> sum(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        ll A; cin >> A;
        sum[i] = A;
        sum[i] += sum[i - 1];
    }

    ll ans = 0;

    for (int L = 1; L <= N; L++) {
        //左端がLの連続した日で、条件を満たすrの一番左を求める
        ll l = L - 1, r = N + 1, m;

        while (r - l > 1) {
            m = (r + l) / 2;
            if (sum[m] - sum[L - 1] >= M)r = m;
            else l = m;
        }

        r = max(r, L + K - 1);
        if (r > N)break;
        ans += N - r + 1;
    }
    
    cout << ans << endl;
}
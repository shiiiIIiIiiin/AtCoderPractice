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
    int N, Q; cin >> N >> Q;
    vector<ll> A(N + 1, 0), sum(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
        sum[i] = sum[i - 1] + A[i];
    }

    for (; Q--;) {
        int t; cin >> t;

        if (t == 1) {
            ll x; cin >> x;

            sum[x] += A[x + 1] - A[x];
            sum[x + 1] = sum[x] + A[x];

            swap(A[x], A[x + 1]);

        }
        else {
            ll l, r; cin >> l >> r;
            cout << sum[r] - sum[l - 1] << endl;
        }
    }
}
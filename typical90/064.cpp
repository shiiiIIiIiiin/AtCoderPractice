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
    vector<ll> A(N + 1);
    for (int i = 1; i <= N; i++)cin >> A[i];

    vector<ll> diff(N + 1);

    ll sum = 0;

    for (int i = 1; i + 1 <= N; i++) {
        diff[i] = A[i] - A[i + 1];
        sum += abs(A[i] - A[i + 1]);
    }

    //diff[i]にはA[i]とA[i+1]の差が格納されている

    for (; Q--;) {
        ll l, r, v; cin >> l >> r >> v;

        /*
        sum -= abs(diff[l - 1]) + abs(diff[r]);

        diff[l - 1] -= v;
        diff[r] += v;

        sum += abs(diff[l - 1]) + abs(diff[r]);
        */

        if (l - 1 != 0) {
            sum -= abs(diff[l - 1]);
            diff[l - 1] -= v;
            sum += abs(diff[l - 1]);
        }

        if (r < N) {
            sum -= abs(diff[r]);
            diff[r] += v;
            sum += abs(diff[r]);
        }

        cout << sum << endl;
    }
}
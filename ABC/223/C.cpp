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
    vector<ll> A(N), B(N);
    double sum = 0;
    for (int i = 0; i < N; i++)cin >> A[i] >> B[i], sum += (double)A[i] / B[i];

    double T = sum / 2, ans = 0;

    //T秒後、火がどこにあるか出力すればいい

    for (int i = 0; i < N; i++) {
        if (T - (double)A[i] / B[i] >= 0) {
            T -= (double)A[i] / B[i];
            ans += A[i];
        }
        else {
            ans += B[i] * T;
            cout << fixed << setprecision(8) << ans << endl;
            return 0;
        }
    }
}
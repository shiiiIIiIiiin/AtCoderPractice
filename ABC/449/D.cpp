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
    int l, r, d, u; cin >> l >> r >> d >> u;
    ll ans = 0;

    //|x|>|y|の場合

    for (int x = (l % 2 == 0 ? l : l + 1); x <= r; x += 2) {
        int D = max(d, -abs(x) + 1), U = min(u, abs(x) - 1), C = U - D + 1;
        ans += max(0, C);
    }

    // |x|<|y|の場合

    for (int y = (d % 2 == 0 ? d : d + 1); y <= u; y += 2) {
        int L = max(l, -abs(y)), R = min(r, abs(y)), C = R - L + 1;
        ans += max(C, 0);
    }

    cout << ans << endl;
}
//#define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
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

ll dx[] = { 1, 0, -1, 0 }, dy[] = { 0, 1, 0, -1 };
const ll INF = LLONG_MAX / 2;

ll N, K;

bool check(ll m, vector<ll>& A) {
    ll res = 0;

    for (int i = 1; i <= N; i++) {
        res += max(0LL, (m - A[i] + i - 1) / i);
        if (res > K)return false;
    }

    return true;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> N >> K;
    vector<ll> A(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    ll l = 0, r = INF, m;

    while (r - l > 1) {
        m = (r + l) / 2;
        if (check(m, A))l = m;
        else r = m;
    }

    cout << l << endl;
}
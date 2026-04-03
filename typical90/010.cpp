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


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    vector<ll> score_sum(N + 1), score_1(N + 1), score_2(N + 1);

    for (int i = 1; i <= N; i++) {
        int c, p; cin >> c >> p;
        score_sum[i] += p;
        if (c == 1) score_1[i] += p;
        else score_2[i] += p;
    }

    for (int i = 1; i <= N; i++) {
        score_sum[i] += score_sum[i - 1];
        score_1[i] += score_1[i - 1];
        score_2[i] += score_2[i - 1];
    }

    int Q; cin >> Q;

    for (; Q--;) {
        int l, r; cin >> l >> r;
        cout << score_1[r] - score_1[l - 1] << " " << score_2[r] - score_2[l - 1] << endl;
    }
}
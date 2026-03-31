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
    int N, A, B; cin >> N >> A >> B;
    vector<vector<int>> cnt_A(N + 1, vector<int>(N + 1, 0)), cnt_B(N + 1, vector<int>(N + 1, 0));

    for (int i = 0; i < A; i++) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        for (int x = a; x <= c; x++)for (int y = b; y <= d; y++)cnt_A[x][y] |= 1;
    }

    for (int i = 0; i < B; i++) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        for (int x = a; x <= c; x++)for (int y = b; y <= d; y++)cnt_B[x][y] |= 1;
    }

    int ans = 0;

    for (int i = 1; i <= N; i++)for (int j = 1; j <= N; j++)ans += cnt_A[i][j] && cnt_B[i][j];

    cout << ans << endl;
}
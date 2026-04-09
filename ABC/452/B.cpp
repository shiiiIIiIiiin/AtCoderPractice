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

    int H, W; cin >> H >> W;
    vector<vector<int>> ans(H, vector<int>(W, 0));

    for (int i = 0; i < H; i++) {
        ans[i][0] = 1;
        ans[i][W - 1] = 1;
    }

    for (int j = 0; j < W; j++) {
        ans[0][j] = 1;
        ans[H - 1][j] = 1;
    }

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++)cout << (ans[i][j] == 0 ? '.' : '#');
        cout << endl;
    }
}
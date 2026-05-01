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


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int H, W; cin >> H >> W;
    vector<string> S(H + 1);
    for (int i = 1; i <= H; i++) {
        string t; cin >> t;
        S[i] = "?" + t;
    }

    int ans = 0;

    for (int h1 = 1; h1 <= H; h1++) {
        for (int h2 = h1; h2 <= H; h2++) {
            for (int w1 = 1; w1 <= W; w1++) {
                for (int w2 = w1; w2 <= W; w2++) {
                    bool res = true;
                    for (int i = h1; i <= h2; i++)for (int j = w1; j <= w2; j++) {
                        if (S[i][j] != S[h1 + h2 - i][w1 + w2 - j])res = false;
                    }

                    ans += res;
                }
            }
        }
    }

    cout << ans << endl;
}
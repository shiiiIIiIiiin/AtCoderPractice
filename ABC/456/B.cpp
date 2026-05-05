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

    cout << fixed << setprecision(10);

    vector<vector<double>> A(3, vector<double>(6));
    for (int i = 0; i < 3; i++)for (int j = 0; j < 6; j++)cin >> A[i][j];

    int cnt = 0;


    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 6; k++) {
                vector<bool> ex(7);
                ex[A[0][i]] = true;
                ex[A[1][j]] = true;
                ex[A[2][k]] = true;

                if (ex[4] && ex[5] && ex[6])cnt++;
            }
        }
    }

    cout << (double)(cnt) / modpow(6LL, 3, INF) << endl;
}
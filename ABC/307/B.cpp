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

    vector<string> S(N);
    for (int i = 0; i < N; i++)cin >> S[i];

    for (int i = 0; i < N; i++)for (int j = 0; j < N; j++) {
        if (i == j)continue;
        string T = S[i] + S[j];
        bool f = true;

        for (int k = 0; k < T.size(); k++)if (T[k] != T[T.size() - 1 - k])f = false;

        if (f) {
            cout << "Yes" << endl;
            return 0;
        }
    }

    cout << "No" << endl;
}
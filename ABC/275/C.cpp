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

using pii = pair<int, int>;
bool is_square(vector<pii> P) {
    //複素数的には a+c=b+dかつ(d-a)^2+(b-a)^2=0でいいらしい

    sort(P.begin(), P.end());

    do {
        vector<complex<int>> C;

        for (auto [x, y] : P) {
            C.push_back(complex<int>({ x,y }));
        }

        if (C[0] + C[2] == C[1] + C[3] && (C[3] - C[0]) * (C[3] - C[0]) + (C[1] - C[0]) * (C[1] - C[0]) == 0)return true;
    } while (next_permutation(P.begin(), P.end()));

    return false;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int N = 9;
    vector<string> S(N);
    for (int i = 0; i < N; i++)cin >> S[i];

    vector<pair<int, int>> P;

    for (int i = 0; i < N; i++)for (int j = 0; j < N; j++)if (S[i][j] == '#')P.push_back({ i,j });

    int M = P.size();
    int ans = 0;

    for (int i = 0; i < M; i++)for (int j = i + 1; j < M; j++)for (int k = j + 1; k < M; k++)for (int l = k + 1; l < M; l++) {
        if (is_square({ P[i], P[j], P[k], P[l] }))ans++;
    }

    cout << ans << endl;
}
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
    vector<int> A(N), B(N);
    for (int i = 0; i < N; i++)cin >> A[i] >> B[i];

    int M; cin >> M;
    vector<string> S(M);
    for (int i = 0; i < M; i++)cin >> S[i];

    vector<vector<vector<bool>>> f(11, vector<vector<bool>>(11, vector<bool>(26)));

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < S[i].size(); j++)f[S[i].size()][j][S[i][j] - 'a'] = true;
    }

    for (int j = 0; j < M; j++) {
        //j個目の問題を解く
        string s = S[j];

        if (s.size() != N) {
            cout << "No" << endl;
            continue;
        }

        bool can = true;
        for (int i = 0; i < N; i++) {

            bool ex = false;

            /*
            for (int k = 0; k < M; k++) {
                if (S[k].size() != A[i])continue;
                if (S[k][B[i] - 1] != s[i])continue;
                ex = true;
            }
                これを高速にする
            */
            ex = f[A[i]][B[i] - 1][s[i] - 'a'];

            if (!ex)can = false;
        }

        cout << (can ? "Yes" : "No") << endl;
    }
}
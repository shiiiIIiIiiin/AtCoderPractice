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
    int N; cin >> N;
    vector<vector<int>> A(N + 1, vector<int>(N + 1)), B(N + 1, vector<int>(N + 1));

    for (int i = 1; i <= N; i++)for (int j = 1; j <= N; j++)cin >> A[i][j];
    for (int i = 1; i <= N; i++)for (int j = 1; j <= N; j++)cin >> B[i][j];

    int cnt = 4;

    while (cnt--) {
        vector<vector<int>> memo = A;

        for (int i = 1; i <= N; i++)for (int j = 1; j <= N; j++) {
            A[i][j] = memo[N + 1 - j][i];
        }

        bool f = true;

        for (int i = 1; i <= N; i++)for (int j = 1; j <= N; j++)if (A[i][j] == 1 && B[i][j] == 0)f = false;

        if (f) {
            cout << "Yes" << endl;
            return 0;
        }
    }

    cout << "No" << endl;
}
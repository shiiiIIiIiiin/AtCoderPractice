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

using mint = modint998244353;

int n;
double dp[301][301][301];

double f(int x, int y, int z) {
    if (x < 0 || y < 0 || z < 0)return 0;
    if (dp[x][y][z] >= 0)return dp[x][y][z];
    int sum = x + y + z;
    return dp[x][y][z] = double(n) / (x + y + z) + f(x, y + 1, z - 1) * ((double)z / sum) + f(x + 1, y - 1, z) * ((double)y / sum) + f(x - 1, y, z) * ((double)x / sum);
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> n;
    vector<int> cnt(3);
    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        cnt[a - 1]++;
    }

    for (int i = 0; i <= 300; i++)for (int j = 0; j <= 300; j++)for (int k = 0; k <= 300; k++)dp[i][j][k] = -1.0;
    dp[0][0][0] = 0;

    /*
     dp[i][j][k]=1
                 +dp[i][j+1][k-1]*(3個の皿を選ぶ確率)
                 +dp[i+1][j-1][k]*(2個の皿を選ぶ確率)
                 +dp[i-1][j][k]*(1個の皿を選ぶ確率)
                 +dp[i][j][k]*(0個の皿を選ぶ確率)


     (1-(0個の皿を選ぶ確率))dp[i][j][k]=1
                                      +dp[i][j+1][k-1]*(3個の皿を選ぶ確率)
                                      +dp[i+1][j-1][k]*(2個の皿を選ぶ確率)
                                      +dp[i-1][j][k]*(1個の皿を選ぶ確率)


     dp[i][j][k]=n/(i+j+k)
                 +dp[i][j+1][k-1]*(k/(i+j+k))
                 +dp[i+1][j-1][k]*(j/(i+j+k))
                 +dp[i-1][j][k]*(i/(i+j+k))
    */

    f(cnt[0], cnt[1], cnt[2]);

    cout << fixed << setprecision(10);
    cout << dp[cnt[0]][cnt[1]][cnt[2]] << endl;
}
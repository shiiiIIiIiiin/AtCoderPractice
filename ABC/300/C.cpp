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

int H, W; 

int check(vector<string>& S, int x, int y) {
    int res = 0;

    while (true) {
        int nxl = x - res, nxr = x + res, nyl = y - res, nyr = y + res;
        if (nxl < 0 || H <= nxr || nyl < 0 || W <= nyr)break;

        if (S[nxl][nyl] == '#' && S[nxl][nyr] == '#' && S[nxr][nyl] == '#' && S[nxr][nyr] == '#')res++;
        else break;
    }
    res--;

    return res;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> H >> W;
    vector<string> S(H);
    for (int i = 0; i < H; i++)cin >> S[i];

    vector<int> cnt(min(H, W) + 1);

    for (int i = 0; i < H; i++)for (int j = 0; j < W; j++) {
        //S[i][j]を中心とするバツ印かどうかを判断する
        if (S[i][j] != '#')continue;

        int c = check(S, i, j);
        cnt[c]++;
    }

    for (int i = 1; i < cnt.size(); i++)cout << cnt[i] << " ";

}
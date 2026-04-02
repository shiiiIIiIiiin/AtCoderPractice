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

    //dp[n]:=さいころを何回か振ったあと、持ってる数字がnである確率
    //この持ち方をすると、多くの要素が0になる。知りたいのはNの約数のdpの値だけ

    ll N; cin >> N;

    map<ll, ll> cnt;
    vector<ll> div = { 2,3,5 };

    ll nc = N;
    for (auto v : div) {
        while (nc % v == 0) {
            nc /= v;
            cnt[v]++;
        }
    }

    if (nc != 1) {//絶対無理な約数を持ってる
        cout << 0 << endl;
        return 0;
    }

    vector<ll> div_n;
    for (int i = 0; i <= cnt[2]; i++)for (int j = 0; j <= cnt[3]; j++)for (int k = 0; k <= cnt[5]; k++) {
        ll n = modpow(2LL, i, INF) * modpow(3LL, j, INF) * modpow(5LL, k, INF);
        div_n.push_back(n);
    }

    sort(div_n.begin(), div_n.end());

    //cout << div_n.size() << endl; //N=979552051200000000 で　2520になった

    map<ll, ll> dp;
    dp[0] = 0;
    dp[1] = 1;

    for (auto n : div_n) {
        for (int i = 2; i <= 6; i++) {
            if (n % i != 0)continue;
            dp[n] += dp[n / i] * modinv(5, MOD);//6じゃないことに注意！！1が出ることもあるから
            dp[n] %= MOD;
        }
    }

    cout << dp[N] << endl;
}
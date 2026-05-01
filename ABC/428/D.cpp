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

    //C+xがd桁である場合を考える
    // 10^(d-1)<=C+x<=10^d -1 より、 10^(d+1)-C <= x <= 10^d - C - 1 かつ 1 <= x <= D の共通範囲をxは動く
    // max(1,10^(d-1)-C) <= x <= min(D, 10^d -C -1 ) の範囲をｘは動く L<=x<=Rとする

    /*
　　　C + ｘ が d桁の場合を考えているので、 f(C,C+x)=C*10^d+C+x　である. よって、 C*10^d+C+L以上C*10^d+C+R 以下の平方数の数を数えればいい
      k以下の平方数の数は[√ｋ]個なので、
      ans+=max(sqrt(C*10^d+C+R)-sqrt(C*10^d+C+L-1),0)
      みたいにして d=1,2,3,・・・,log_10(C+D)で足し合わせればいい
    */

    int T; cin >> T;

    for (; T--;) {
        ll C, D; cin >> C >> D;
        ll ans = 0;

        for (int d = 1; d <= 12; d++) {
            ll L = max(1LL, modpow(10LL, d - 1, INF) - C), R = min(D, modpow(10LL, d, INF) - C - 1);
            ans += max(ll(sqrtl(C * modpow(10LL, d, INF) + C + R)) - ll(sqrtl(C * modpow(10LL, d, INF) + C + L - 1)), 0LL);
        }

        cout << ans << endl;
    }
}
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

//cin.tie(nullptr);
//ios::sync_with_stdio(false);

ll solve(ll A, ll X, ll M) {
    if (X == 0)return 0;
    if (X % 2 == 1)return (solve(A, X - 1, M) + modpow(A, X - 1, M)) % M;
    else return (solve(A, X / 2, M) * (1 + modpow(A, X / 2, M))) % M;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    /*
     等比数列の和の公式で一発で出すことを考える
　　　フェルマーの小定理の使い方（分母）に注意
     と思ったが、A-1がMと互いに素でない時、逆元を持たないことになるのでやばい
    */

    ll A, X, M; cin >> A >> X >> M;

    /*
    答えをf(A,X,M)とすると、
　　X=0なら、f(A,0,M)=0
    Xが奇数の時は、f(A,X,M)=f(A,X-1,M)+A^(X-1) mod M
    Xが偶数の時は、f(A,X,M)=f(A,X/2,M)*(1+A^(X/2)) mod M
    */

    //分割統治法でやれる

    cout << solve(A, X, M) << endl;
}
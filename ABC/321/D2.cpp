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

    ll N, M, P; cin >> N >> M >> P;
    vector<ll> A(N), B(M);
    for (int i = 0; i < N; i++)cin >> A[i];
    for (int i = 0; i < M; i++)cin >> B[i];

    sort(B.begin(), B.end());
    ll ans = 0;
    vector<ll> sum(M + 1);
    for (int i = 1; i <= M; i++)sum[i] = sum[i - 1] + B[i - 1];

    for (int i = 0; i < N; i++) {
        
        /*主食をiとしたとき、
        A[i] + B[l] <= Pとなるようなものに対してはA[i]+B[l]円
        そうではないものに対してはP円にする
　　　　　前半は二分探索、後半は累積和で高速に求めることができる
        */

        ll r = upper_bound(B.begin(), B.end(), P - A[i]) - B.begin();
        ans += P * (M - r);
        ans += A[i] * r + sum[r];
    }

    cout << ans << endl;
}
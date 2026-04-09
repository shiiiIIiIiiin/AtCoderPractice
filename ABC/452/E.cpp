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

    using mint = modint998244353;

    ll N, M; cin >> N >> M;
    vector<mint> A(N + 1), B(M + 1);
    for (int i = 1; i <= N; i++) {
        ll tmp; cin >> tmp;
        A[i] = tmp;
    }
    for (int j = 1; j <= M; j++) {
        ll tmp; cin >> tmp;
        B[j] = tmp;
    }
    // i % j = i - [i / j] * j
/*

ΣΣ{Ai* Bj * (i - [i / j] * j)}

Σ(A[i]*i)ΣB[j]-ΣB[j]*jΣA[i]*([i/j])
*/
    vector<mint> sumA(N + 1);
    mint ans = 0, sumAii = 0, sumB = 0;
    for (int i = 1; i <= N; i++) {
        sumAii += A[i] * i;
        sumA[i] = sumA[i - 1] + A[i];
    }

    for (int j = 1; j <= M; j++)sumB += B[j];

    ans = sumAii * sumB;

    for (ll j = 1; j <= M; j++) {
        mint sum_Ai_floor = 0;
        for (ll k = 1; k <= N / j; k++) {
            //[i/j]=kとなる部分を足す
            ll r = min(N, (k + 1) * j - 1), l = k * j;
            sum_Ai_floor += (sumA[r] - sumA[l - 1]) * k;
        }

        ans -= B[j] * j * sum_Ai_floor;
    }

    cout << ans.val() << endl;
}
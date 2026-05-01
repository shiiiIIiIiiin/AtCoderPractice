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
    vector<ll> A(N + 1, INF), B(N + 1, INF);
    for (int i = 2; i <= N; i++)cin >> A[i];
    for (int i = 3; i <= N; i++)cin >> B[i];

    vector<ll> dp(N + 1, INF);
    dp[1] = 0;

    for (int i = 2; i <= N; i++)dp[i] = min(dp[i - 1] + A[i], dp[i - 2] + B[i]);

    //復元をする
    vector<int> ans;
    int pos = N;
    ans.push_back(N);

    while (pos > 1) {
        if (dp[pos] == dp[pos - 1] + A[pos]) {
            ans.push_back(pos - 1);
            pos = pos - 1;
        }
        else {
            ans.push_back(pos - 2);
            pos = pos - 2;
        }
    }

    reverse(ans.begin(), ans.end());

    cout << ans.size() << endl;
    for (auto v : ans)cout << v << " ";
}
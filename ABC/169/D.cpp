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

    ll N; cin >> N;
    map<ll, ll> mp;

    vector<bool> is_prime(2e6, true);
    is_prime[0] = is_prime[1] = false;
    vector<ll> primes;

    for (ll i = 2; i < is_prime.size(); i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = 2 * i; j < is_prime.size(); j += i)is_prime[j] = false;
        }
    }

    for (int i = 0; i < primes.size(); i++) {
        ll p = primes[i];

        while (N % p == 0) {
            N /= p;
            mp[p]++;
        }

    }

    if (N != 1)mp[N] = 1;

    ll ans = 0;

    for (auto [p, c] : mp) {
        // n(n + 1) / 2がcを超えない最大のnをansに足す
        int n = 0;
        while (n * (n + 1) / 2 <= c)n++;
        ans += n - 1;
    }

    cout << ans << endl;
}
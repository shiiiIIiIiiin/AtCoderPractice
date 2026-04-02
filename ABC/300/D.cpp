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
    vector<ll> primes;
    vector<bool> is_prime(1e6 + 10, true);

    is_prime[0] = is_prime[1] = false;

    for (ll i = 2; i < is_prime.size(); i++) {
        if (!is_prime[i])continue;
        primes.push_back(i);
        for (ll j = 2 * i; j < is_prime.size(); j += i)is_prime[j] = false;
    }

    //cout << primes.size() << endl; 78499が出力された

    /*
    aを全探索する？→a^5<N より、a<N^(1/5)の範囲を全探索すればいい
    */

    ll ans = 0;

    for (int i = 0; i < primes.size(); i++) {
        ll a = primes[i];
        if (a * a * a * a * a >= N)break;
        for (int j = i + 1; j < primes.size(); j++) {
            ll b = primes[j];
            if (a * a * b * b * b >= N)break;
            for (int k = j + 1; k < primes.size(); k++) {
                ll c = primes[k];
                if (a * a * b * c * c > N)break;
                ans++;
            }
        }
    }

    cout << ans << endl;
}
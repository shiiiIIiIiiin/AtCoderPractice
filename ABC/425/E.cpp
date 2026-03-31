//GPT解
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// fast pow (mod)
static inline ll modpow(ll a, ll e, ll mod) {
    ll r = 1 % mod;
    a %= mod;
    while (e) {
        if (e & 1) r = (__int128)r * a % mod;
        a = (__int128)a * a % mod;
        e >>= 1;
    }
    return r;
}

// inline f(n,p): exponent of prime p in n!
static inline ll vp_in_fact(ll n, int p) {
    ll cnt = 0;
    while (n) {
        n /= p;
        cnt += n;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    ll M;
    if (!(cin >> T >> M)) return 0;

    // precompute primes up to 5000
    const int LIM = 5000;
    vector<int> primes;
    vector<char> is_prime(LIM + 1, 1);
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i * i <= LIM; ++i) if (is_prime[i]) {
        for (int j = i * i; j <= LIM; j += i) is_prime[j] = 0;
    }
    for (int i = 2; i <= LIM; ++i) if (is_prime[i]) primes.push_back(i);

    while (T--) {
        int N; cin >> N;
        vector<ll> C(N);
        ll sum = 0;
        for (int i = 0; i < N; ++i) { cin >> C[i]; sum += C[i]; }

        ll ans = 1 % M;

        // For each prime p <= sum (but primes list limited to 5000)
        for (int p : primes) {
            if ((ll)p > sum) break;
            ll c = vp_in_fact(sum, p);

            // s = sum_{i} v_p(C[i]!)
            ll s = 0;
            for (int i = 0; i < N; ++i) {
                // compute v_p(C[i]!)
                ll x = C[i];
                while (x) { x /= p; s += x; }
            }

            if (c > s) {
                ll k = c - s;
                ans = ( (__int128)ans * modpow(p, k, M) ) % M;
            }
        }

        cout << ans << '\n';
    }
    return 0;
}

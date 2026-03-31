#include <iostream>
#include <vector>
#include <string>
using namespace std;
using ll = long long;

const ll MOD = 998244353;
const int MAX = 5005;

vector<ll> fact(MAX), inv_fact(MAX);

// a^b % mod
ll modpow(ll a, ll b, ll mod) {
	ll res = 1;
	while (b > 0) {
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}

// 前計算：階乗とその逆元
void precompute() {
	fact[0] = 1;
	for (int i = 1; i < MAX; i++) fact[i] = fact[i - 1] * i % MOD;

	inv_fact[MAX - 1] = modpow(fact[MAX - 1], MOD - 2, MOD);
	for (int i = MAX - 2; i >= 0; i--) inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;
}

// nCr を O(1) で計算
ll nCr(ll n, ll r) {
	if (r < 0 || r > n) return 0;
	return fact[n] * inv_fact[r] % MOD * inv_fact[n - r] % MOD;
}

int main() {
	precompute();

	string S; cin >> S;
	int N = S.size();
	vector<ll> cnt(27, 0);
	for (char c : S) cnt[c - 'a' + 1]++;

	vector<vector<ll>> dp(27, vector<ll>(N + 1, 0));
	dp[0][0] = 1;

	for (int i = 1; i <= 26; i++) {
		for (int j = 0; j <= N; j++) {
			for (int k = 0; k <= min(j, (int)cnt[i]); k++) {
				ll add = dp[i - 1][j - k] * nCr(j, k) % MOD;
				dp[i][j] = (dp[i][j] + add) % MOD;
			}
		}
	}

	ll ans = 0;
	for (int i = 1; i <= N; i++) {
		ans = (ans + dp[26][i]) % MOD;
	}
	cout << ans << endl;
}

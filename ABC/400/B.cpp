#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <map>
#include <set>
#include <iterator>
#include <unordered_map>
#include <stack>
#include <string>
#include <cmath>
#include <iomanip>
#include <deque>

using namespace std;
using ll = long long;

const ll MOD = 998244353;
const ll MOD2 = 1'000'000'007;

long long modinv(long long a, long long m) {//mod. m での a の逆元 a^{-1} を計算する
	long long b = m, u = 1, v = 0;
	while (b) {
		long long t = a / b;
		a -= t * b; swap(a, b);
		u -= t * v; swap(u, v);
	}
	u %= m;
	if (u < 0) u += m;
	return u;
}

long long modpow(long long a, long long n, long long mod) {// a^n mod を計算する
	long long res = 1;
	while (n > 0) {
		if (n & 1) res = res * a % mod;
		a = a * a % mod;
		n >>= 1;
	}
	return res;
}

ll power(ll x, ll c) {
	ll res = 1;

	for (int i = 0; i < c; i++) {
		res *= x;

		if (res > 1'000'000'000)return -1;
	}

	return res;
}

int main() {
	ll N, M; cin >> N >> M;
	ll ans = 0;

	for (ll i = 0; i <= M; i++) {
		if(power(N,i)!=-1)ans += power(N, i);
		else {
			cout << "inf";
			return 0;
		}

		if (ans > 1'000'000'000) {
			cout << "inf" << endl;
			return 0;
		}
	}

	cout << ans << endl;
}
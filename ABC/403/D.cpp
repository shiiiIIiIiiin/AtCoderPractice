//#define _GLIBCXX_DEBUG

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
#include <unordered_set>

using namespace std;
using ll = long long;

const ll MOD = 998244353;
const ll MOD2 = 1'000'000'007;

class SegTree {
public:
	vector<ll> dat;
	ll siz = 1;

	SegTree(ll n) {
		while (siz < n)siz *= 2;
		dat.resize(2 * siz, -LLONG_MAX);
	}

	void update(int id, ll x) {
		id += siz;
		dat[id] = x;
		while (id != 0) {
			id /= 2;
			dat[id] = max(dat[2 * id], dat[2 * id + 1]);
		}
	}

	ll getval(int id) {
		return dat[id + siz];
	}

	ll getmax(ll L, ll R, ll a, ll b, ll u) {
		if (b <= L || R <= a)return -LLONG_MAX / 2;
		if (L <= a && b <= R)return dat[u];

		ll m = (a + b) / 2;

		return max(getmax(L, R, a, m, 2 * u), getmax(L, R, m, b, 2 * u + 1));
	}
};

class UnionFind {
public:
	vector<int> siz, par;

	UnionFind(int n) {
		siz.resize(n, 1);
		par.resize(n, -1);
	}

	int root(int x) {
		if (par[x] == -1) return x;
		return par[x] = root(par[x]);
	}

	void unite(int x, int y) {
		int rx = root(x), ry = root(y);
		if (rx == ry)return;

		if (siz[rx] < siz[ry]) {
			par[rx] = ry;
			siz[ry] += siz[rx];
		}
		else {
			par[ry] = rx;
			siz[rx] += siz[ry];
		}

	}

	bool same(int x, int y) {
		return root(x) == root(y);
	}

};

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

int dx[] = { 1,0,-1,0 }, dy[] = { 0,1,0,-1 };

int main() {
	ll N, D; cin >> N >> D;
	vector<ll> A(N);
	for (int i = 0; i < N; i++)cin >> A[i];

	//sort(A.begin(), A.end());

	map<ll, ll> cntnum;
	ll M = -1;
	for (int i = 0; i < N; i++) {
		cntnum[A[i]]++;
		M = max(M, A[i]);
	}

	if (D == 0) {
		ll ans = 0;
		for (auto p : cntnum)if (p.second > 1)ans += p.second - 1;
		cout << ans << endl;
		return 0;
	}

	vector<vector<ll>> u(D, vector<ll>(M / D + 2));

	for (auto p : cntnum) {
		ll id = p.first, c = p.second;
		// u[id % D].push_back(c);
		u[id % D][id / D] += c;
	}

	ll ans = 0;

	for (int i = 0; i < D; i++) {
		vector<vector<ll>> dp(2, vector<ll>(u[i].size() + 1, 0));//dp[0][i]...数列のi個目を使って一番大きくなる、dp[1][i]...i番目を使わずに

		dp[0][0] = 0, dp[1][0] = 0;
		ll sum = 0;

		for (int j = 1; j <= u[i].size(); j++) {
			dp[0][j] = dp[1][j - 1] + u[i][j - 1];//使う
			dp[1][j] = max(dp[0][j - 1], dp[1][j - 1]);//使わない

			sum += u[i][j - 1];
		}

		ans += sum - max(dp[0][u[i].size()], dp[1][u[i].size()]);
	}

	cout << ans << endl;
}
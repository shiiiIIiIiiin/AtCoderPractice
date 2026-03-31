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
		dat.resize(2 * siz, LLONG_MAX/2);
	}

	void update(int id, ll x) {
		id += siz;
		dat[id] = x;
		while (id != 0) {
			id /= 2;
			dat[id] = min(dat[2 * id], dat[2 * id + 1]);
		}
	}

	ll getval(int id) {
		return dat[id + siz];
	}

	ll getmin(ll L, ll R, ll a, ll b, ll u) {
		if (b <= L || R <= a)return LLONG_MAX / 2;
		if (L <= a && b <= R)return dat[u];

		ll m = (a + b) / 2;

		return min(getmin(L, R, a, m, 2 * u), getmin(L, R, m, b, 2 * u + 1));
	}

	/*
	ll getmin(ll l, ll r) {
		return getmin(l, r, 0, siz, 1);
	}
	*/
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
	int T; cin >> T;

	for (; T--;) {
		int N; cin >> N;
		vector<int> A(2 * N);
		for (int i = 0; i < 2 * N; i++)cin >> A[i];

		vector<vector<int>> memo(N + 1);
		for (int i = 0; i < 2 * N; i++) {
			memo[A[i]].push_back(i);
		}

		int ans = 0;
		set<pair<int, int>> st;
		for (int i = 0; i + 1 < 2 * N; i++) {
			if (A[i] == A[i + 1])continue;

			vector<int> u, v;
			u.push_back(memo[A[i]][0]);
			u.push_back(memo[A[i]][1]);
			v.push_back(memo[A[i + 1]][0]);
			v.push_back(memo[A[i + 1]][1]);

			sort(u.begin(), u.end());
			sort(v.begin(), v.end());

			if (u[0] + 1 == u[1] || v[0] + 1 == v[1])continue;//隣り合っていたらやめる

			if (!st.count({ A[i],A[i + 1] }) && abs(u[0]-v[0]) == 1 && abs(u[1]-v[1]) == 1) {
				ans++;
				st.insert({ A[i],A[i + 1] });
				st.insert({ A[i + 1],A[i] });
			}
		}

		cout << ans << endl;
	}
}
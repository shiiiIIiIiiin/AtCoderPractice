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
	ll N, M; cin >> N >> M;
	vector<ll> C(N + 1), K(M + 1);
	vector<vector<bool>> A(N + 1, vector<bool>(M + 1, false));
	for (int i = 1; i <= N; i++)cin >> C[i];

	for (int i = 1; i <= M; i++) {
		cin >> K[i];
		for (int j = 0; j < K[i]; j++) {
			int a; cin >> a;
			A[a][i] = true;//動物iを動物園aで見ることができる
		}
	}

	//同じ動物園を３回以上訪れる必要はないので、0,1,2回のうち何回訪れるかを全探索する

	
	ll ans = LLONG_MAX / 2;

	for (ll i = 0; i < modpow(3LL, N, LLONG_MAX / 2); i++) {
		ll k = i, memo = 0;
		vector<ll> viscnt(N + 1, 0);
		for (int j = 1; j <= N; j++) {
			viscnt[j] = k % 3;
			k /= 3;
		}

		vector<int> cnt(M + 1, 0);

		
		for (int j = 1; j <= N; j++) {
			for (int l = 1; l <= M; l++) {
				if (A[j][l]) {
					cnt[l] += viscnt[j];//動物園jで動物lが見れるならcnt[l]を増やす
				}
			}

			memo += C[j] * viscnt[j];
		}

		bool can = true;

		for (int j = 1; j <= M; j++)if (cnt[j] <= 1)can = false;

		if (can)ans = min(ans, memo);
		
	}

	cout << ans << endl;
	
}
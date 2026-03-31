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


ll N, M;

class edge {
public:
	ll to, w;
	edge(ll a, ll b) {
		to = a;
		w = b;
	}
};



int main() {
	cin >> N >> M;
	vector<vector<edge>> G(N + 1);
	for (int i = 0; i < M; i++) {
		ll u, v, w; cin >> u >> v >> w;
		edge e(v, w);
		G[u].push_back(e);
	}

	//bitXOR...奇数回立ってるところを通ると立つ、偶数回で立たない

	//ビットごとに考える？？
	//それぞれの辺は偶数回通るか奇数回通るかのみ変わる->３回以上通ることを考える必要はない

	ll MAXXOR = 1024;

	vector<vector<ll>> dist(N + 1, vector<ll>(MAXXOR, LLONG_MAX / 2));
	dist[1][0] = 0;

	queue<pair<int, int>> q;
	q.push({ 1, 0 });

	while (!q.empty()) {
		pair<ll,ll> u = q.front();
		ll pos = u.first, xval = u.second;
		q.pop();

		for (auto& e : G[pos]) {
			int nx = e.to;
			int nxval = xval ^ e.w;
			if (dist[nx][nxval] == LLONG_MAX / 2) {
				dist[nx][nxval] = dist[pos][xval] + 1;
				q.push({ nx, nxval });
			}
		}
	}

	
	ll ans = LLONG_MAX / 2;
	for (ll x = 0; x < MAXXOR; x++) {
		if (dist[N][x] != LLONG_MAX / 2) ans = min(ans, x);
	}

	
	cout << (ans == LLONG_MAX / 2 ? -1 : ans) << endl;
}
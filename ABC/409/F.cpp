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

ll d(ll x, ll y, vector<pair<ll, ll>>& P) {
	return labs(P[x].first - P[y].first) + labs(P[x].second - P[y].second);
}

class edge {
public:
	ll d, u, v;

	edge(ll D, ll U, ll V) {
		d = D;
		u = U;
		v = V;
	}

	void setup(ll D, ll U, ll V) {
		d = D;
		u = U;
		v = V;
	}


	bool operator<(const edge& other) const {
		return d > other.d;
	}


};

int main() {
	int N, Q; cin >> N >> Q;
	vector<pair<ll, ll>> P(N + 1);
	for (int i = 1; i <= N; i++)cin >> P[i].first >> P[i].second;
	priority_queue<edge> dist;

	for (int i = 1; i < N; i++)for (int j = i + 1; j <= N; j++) {
		edge e(d(i, j, P), i, j);
		dist.push(e);
	}

	UnionFind uf(N + 1+1600);

	for (; Q--;) {
		int type; cin >> type;

		if (type == 1) {
			ll a, b; cin >> a >> b;
			int n = P.size();
			P.push_back({ a,b });
			for (int i = 1; i < n; i++) {
				edge e(d(i, n, P), i, n);
				dist.push(e);
			}
		}


		else if (type == 2) {
			vector<edge> Edges;
			edge e(-100,-100,-100);

			while (!dist.empty()) {
				e = dist.top();

				if (uf.same(e.u, e.v)) {
					dist.pop();//使えないので削除
					continue;
				}

				//最小距離のedge.dを基準にまとめて集める
				ll target_d = e.d;

				while (!dist.empty() && dist.top().d == target_d) {
					auto cur = dist.top(); dist.pop();
					if (!uf.same(cur.u, cur.v)) {
						Edges.push_back(cur);
					}
				}

				//使えるエッジがあった場合
				if (!Edges.empty()) {
					for (auto& ed : Edges) {
						uf.unite(ed.u, ed.v);
					}
					cout << target_d << endl;
				}
				else continue;

				break;
			}

			if (Edges.empty()) {
				cout << -1 << endl;
			}
		}



		else {
			ll u, v; cin >> u >> v;
			cout << (uf.same(u, v) ? "Yes" : "No") << endl;
		}
	}
}
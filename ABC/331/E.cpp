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

using namespace std;
using ll = long long;


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


/*
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
*/

int main() {
	//各主菜に対して一番高い副菜を調べる
	//segtreeを用いて調べることができる

	int N, M, L; cin >> N >> M >> L;
	vector<int> a(N+1), b(M+1);
	for (int i = 1; i <= N; i++)cin >> a[i];
	for (int i = 1; i <= M; i++)cin >> b[i];
	vector<vector<int>> G(N + 1);//各主菜に合わせられない食材をメモする

	for (int i = 0; i < L; i++) {
		int c, d; cin >> c >> d;
		G[c].push_back(d);
	}

	SegTree sg(M + 1);
	for (int i = 1; i <= M; i++)sg.update(i, b[i]);
	ll ans = -1;

	for (int i = 1; i <= N; i++) {//主菜がiの時
		for (auto x : G[i]) {
			sg.update(x, -LLONG_MAX / 2);
		}

		ans = max(ans, a[i] + sg.getmax(1, M + 1, 1, M + 1, 1));

		for (auto x : G[i]) {
			sg.update(x, b[x]);
		}
	}

	cout << ans << endl;
}
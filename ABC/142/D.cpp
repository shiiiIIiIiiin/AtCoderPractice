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

ll gcd(ll x, ll y) {
	if (y == 0)return x;
	return gcd(y, x % y);
}

map<int, ll> yakusu(ll x) {
	map<int, ll> res;
	for (ll i = 2; i * i <= x; i++) {
		while (x % i == 0) {
			res[i]++;
			x /= i;
		}
	}

	if (x > 1)res[x]++;
	return res;
}

int main() {
	//AとBの公約数はAとBの最大公約数の約数である
	ll A, B; cin >> A >> B;
	if (A > B)swap(A, B);

	map<int, ll> div = yakusu(gcd(A, B));
	cout << div.size() + 1;
}
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

int main() {
	ll N, M; cin >> N >> M;
	vector<vector<pair<ll, ll>>> G(N + 1);
	for (int i = 0; i < M; i++) {
		ll a, b, c; cin >> a >> b >> c;
		G[a].push_back({ b,c });
		G[b].push_back({ a,c });
	}

	vector<vector<ll>> cur(2, vector<ll>(N + 1, LLONG_MAX / 2));
	vector<vector<bool>> kakutei(2, vector<bool>(N + 1, false));
	vector<priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>>> Q(2);

	//頂点1と頂点Nからのダイクストラ法

	for (int i = 0; i < 2; i++) {//2回のダイクストラ法を使う

		if (i == 1) {
			Q[i].push({ 0,1 });
			cur[i][1] = 0;
		}
		else {
			Q[i].push({ 0,N });
			cur[i][N] = 0;
		}

		while (!Q[i].empty()) {
			ll pos = Q[i].top().second; Q[i].pop();
			if (kakutei[i][pos])continue;
			kakutei[i][pos] = true;
			
			for (int k = 0; k < G[pos].size(); k++) {
				auto [nex, cost] = G[pos][k];

				if (kakutei[i][nex])continue;
				

				if (cur[i][nex] > cur[i][pos] + cost) {
					cur[i][nex] = cur[i][pos] + cost;
					Q[i].push({ cur[i][nex],nex });
				}
			}
		}
	}

	for (int i = 1; i <= N; i++) {
		cout << cur[0][i] + cur[1][i] << endl;
	}

}
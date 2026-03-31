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

int main() {
	int N, M; cin >> N >> M;
	vector<vector<pair<ll, ll>>> G(N + 1);
	vector<ll> U(M + 1), V(M + 1), T(M + 1);
	for (int i = 1; i <= M; i++) {
		ll u, v, t; cin >> u >> v >> t;
		U[i] = u, V[i] = v, T[i] = t;
		G[u].push_back({ v,t });
		G[v].push_back({ u,t });
	}


	vector<vector<ll>> dist(N + 1, vector<ll>(N + 1, LLONG_MAX / 2));
	//ここでダイクストラ法を各頂点から行って任意の２点間の最小距離を求めておく


	for (int s = 1; s <= N; ++s) {
		priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
		dist[s][s] = 0;
		pq.push({ 0, s });

		while (!pq.empty()) {
			auto [d, u] = pq.top(); pq.pop();
			if (d > dist[s][u]) continue;

			for (auto [v, cost] : G[u]) {
				if (dist[s][v] > dist[s][u] + cost) {
					dist[s][v] = dist[s][u] + cost;
					pq.push({ dist[s][v], v });
				}
			}
		}
	}

	int Q; cin >> Q;

	for (; Q--;) {
		int K; cin >> K;
		vector<int> B(K);
		ll ans = LLONG_MAX / 2;

		for (int i = 0; i < K; i++)cin >> B[i];

		//solve------------------
		
		//橋をどの順にどの向きで渡るかを全探索する
		vector<int> P(K);
		for (int i = 0; i < K; i++)P[i] = i;


		do {

			for (int i = 0; i < 1 << K; i++) {//どの向きで渡るか
				ll memo = 0, pos = 1;

				for (int j = 0; j < K; j++) {
					int nex_target;
					int bridge = B[P[j]];
					if ((i >> j) & 1)nex_target = U[bridge];
					else nex_target = V[bridge];

					memo += dist[pos][nex_target];//現在地から次の橋の始まりまで
					memo += T[bridge];

					pos = ((i >> j) & 1 ? V[bridge] : U[bridge]);

				}
				memo += dist[pos][N];

				ans = min(ans, memo);
			}
		} while (next_permutation(P.begin(), P.end()));




		
		//-----------------------

		cout << ans << endl;
	}
}
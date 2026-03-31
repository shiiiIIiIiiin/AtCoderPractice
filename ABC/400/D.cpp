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



int H, W;

int mid(int x, int y) {
	return x * W + y;
}

int main() {
	/*
	グラフに落とし込んで考える
	グラフGを頂点HW個のグラフとし、コストが０か１の辺を適切に張ることで最短経路問題に落とし込む
	*/


	cin >> H >> W;
	vector<string> S(H);
	for (int i = 0; i < H; i++)cin >> S[i];
	int sx, sy, gx, gy;
	cin >> sx >> sy >> gx >> gy;
	sx--, sy--, gx--, gy--;

	vector<vector<pair<int, int>>> G(H * W);

	for (int i = 0; i < H; i++) {//適切なグラフを構築する
		for (int j = 0; j < W; j++) {
			//G[i][j]に加えるべき辺について考える
			int id = mid(i, j);

			for (int d = 0; d < 4; d++) {
				int nx = i + dx[d], ny = j + dy[d];
				if (nx < 0 || H <= nx || ny < 0 || W <= ny)continue;
				int nexid = mid(nx, ny);
				
				if (S[nx][ny] == '.')G[id].push_back({ nexid,0 });
				else G[id].push_back({ nexid,1 });
				
				//以下２つ奥を見る
				int nnx = nx + dx[d], nny = ny + dy[d];
				if (nnx < 0 || H <= nnx || nny < 0 || W <= nny)continue;
				nexid = mid(nnx, nny);

				if (S[nnx][nny] == '#' || S[nx][ny] == '#') {
					G[id].push_back({ nexid,1 });
				}
			}
		}
	}

	int sid = mid(sx, sy), gid = mid(gx, gy);//sidからgidに移動する最小を求める

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push({ 0,sid });
	vector<bool> kakutei(H * W, false);
	
	while (!pq.empty()) {
		auto [cost, pos] = pq.top(); pq.pop();

		if (pos == gid) {
			cout << cost << endl;
			return 0;
		}

		if (kakutei[pos])continue;

		kakutei[pos] = true;

		for (int i = 0; i < G[pos].size(); i++) {
			int nex = G[pos][i].first, nc = G[pos][i].second;
			if (kakutei[nex])continue;
			pq.push({ cost + nc,nex });
		}
	}
}
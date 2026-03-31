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



int N, M;

bool dfs_check(vector<vector<ll>>& G,ll pos,vector<bool>& used) {
	if (pos == N)return true;

	for (int i = 0; i < G[pos].size(); i++) {
		int nxt = G[pos][i];

		if (used[nxt])continue;

		used[nxt] = true;
		if (dfs_check(G, nxt, used)) {
			//used[nxt] = false;
			return true;
		}

		//used[nxt] = false;全探索するわけじゃないならいらないのでは？
	}

	return false;
}

int main() {
	cin >> N >> M;
	vector<ll> u(M), v(M), w(M);
	for (int i = 0; i < M; i++)cin >> u[i] >> v[i] >> w[i];

	vector<bool> remain(M, true);//辺iは使ってもいいか？
	ll ans = 0;

	for (ll b = 30; b >= 0; b--) {//bビット目を立てずにゴールできるか
		vector<vector<ll>> G(N + 1);
		vector<int> to_restore;
		
		for (int i = 0; i < M; i++) {//辺のbビット目が立ってない辺だけで作る
			if ((w[i] & (1LL << b)) != 0 || !remain[i]) {
				to_restore.push_back(i);//到達できたらここにある辺全部消す
				continue;
			}

			G[u[i]].push_back(v[i]);
			G[v[i]].push_back(u[i]);
		}

		vector<bool> used(N + 1, false);
		used[1] = true;

		if (dfs_check(G, 1, used)) {//到達できるなら
			for (auto idx : to_restore)remain[idx] = false;//ダメな辺を消す
		}
		else {
			ans |= (1LL << b);
		}
	}

	cout << ans << endl;

}

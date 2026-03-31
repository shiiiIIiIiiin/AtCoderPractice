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

const int N = 4;
void kaiten(vector<string>& P) {
	vector<string> memo = P;
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			P[i][j] = memo[N - 1 - j][i];
		}
	}
}

bool check(vector<vector<string>>& P, int s, int t, int u) {
	int k = 2 * N - 1;
	vector<vector<bool>> put(N, vector<bool>(N, false));

	vector<int> x(3), y(3);
	x[0] = s / k, y[0] = s % k, x[1] = t / k, y[1] = t % k, x[2] = u / k, y[2] = u % k;

	for (int i = 0; i < 3; i++) {//ポリオミノiを配置する
		
		for (int X = 0; X < N; X++)for (int Y = 0; Y < N; Y++) {
			if (P[i][X][Y] == '#') {
				int u = X + (x[i] - 3), v = Y + (y[i] - 3);

				if (u < 0 || N <= u || v < 0 || N <= v)return false;//無理

				if (put[u][v])return false;//もう置いてたらダメ
				put[u][v] = true;
			}
		}
	}

	//for (int i = 0; i < N; i++)for (int j = 0; j < N; j++)if (!put[i][j])return false;//空いてるところがあればダメ
	//↑個数が１６で確定ならこれいらない説
	return true;
}

int main() {
	vector<vector<string>> P(3, vector<string>(4));
	int N = P[0].size();

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			cin >> P[i][j];
		}
	}

	int cnt = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < N; j++)for (int k = 0; k < N; k++)if (P[i][j][k] == '#')cnt++;
	}

	if (cnt != 16) {
		cout << "No";
		return 0;
	}

	for (int i = 0; i < 4; i++) {
		
		for (int j = 0; j < 4; j++) {
			
			//ここで全探索する

			//どこから始めるか16*16*16通り
			//checkに16*3回

			for (int x1 = 0; x1 <49 ; x1++)for (int x2 = 0; x2 < 49; x2++)for (int x3 = 0; x3 < 49; x3++) {
				if (check(P, x1, x2, x3)) {
					cout << "Yes" << endl;
					return 0;
				}
			}

			//ポリオミノ２を90*i°,3を90*j°回転させる
			kaiten(P[2]);

		}
		kaiten(P[1]);
	}

	cout << "No";
	return 0;
}
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
		dat.resize(2 * siz, LLONG_MAX/2);
	}

	void update(int id, ll x) {
		id += siz;
		dat[id] = x;
		while (id != 0) {
			id /= 2;
			dat[id] = min(dat[2 * id], dat[2 * id + 1]);
		}
	}

	ll getval(int id) {
		return dat[id + siz];
	}

	ll getmin(ll L, ll R, ll a, ll b, ll u) {
		if (b <= L || R <= a)return LLONG_MAX / 2;
		if (L <= a && b <= R)return dat[u];

		ll m = (a + b) / 2;

		return min(getmin(L, R, a, m, 2 * u), getmin(L, R, m, b, 2 * u + 1));
	}

	/*
	ll getmin(ll l, ll r) {
		return getmin(l, r, 0, siz, 1);
	}
	*/
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

const ll BASE = 31;

void com_hash(string S, vector<ll>& Hash) {//文字列Sのハッシュを計算する
	int N = S.size();
	Hash.resize(N + 1, 0);

	ll res = 0;
	for (int i = 0; i < N; i++) {
		res += ll(S[i]);
		Hash[i + 1] = res;
		res *= BASE;
		res %= MOD;
	}
}

long long get_hash(int l, int r, const vector<long long>& Hash) {
	long long res = (Hash[r + 1] - (Hash[l] * modpow(BASE, r - l + 1, MOD) % MOD) + MOD) % MOD;
	return res;
}

int main() {
	string S; cin >> S;
	ll N = S.size();
	
	vector<ll> hash, hashr;
	com_hash(S, hash);
	reverse(S.begin(), S.end());
	com_hash(S, hashr);

	int cnt = 0;
	
	for (int i = 0; i < N; i++) {//Sの接頭辞で最大の回文を求める
		ll u = get_hash(0, i, hashr), v = get_hash(N - 1 - i, N - 1, hash);

		if (u == v)cnt = i;
	}

	string t = S.substr(cnt + 1, N);
	reverse(S.begin(), S.end());
	S += t;
	
	cout << S << endl;
	
}
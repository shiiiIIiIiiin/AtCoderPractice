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


class Tube {
public:
	vector<double> col;
	pair<int, int> to_make;

	Tube() {
		col.resize(3);
	}
};

double cal_score(Tube a, Tube b) {
	return (a.col[0] - b.col[0]) * (a.col[0] - b.col[0]) + (a.col[1] - b.col[1]) * (a.col[1] - b.col[1]) + (a.col[2] - b.col[2]) * (a.col[2] - b.col[2]);
}

int main() {
	int N, K, H, T, D; cin >> N >> K >> H >> T >> D;
	vector<Tube> own(K), target(H);

	for (int i = 0; i < K; i++) {
		cin >> own[i].col[0] >> own[i].col[1] >> own[i].col[2];
		own[i].to_make = { -1,i };

	}
	for (int i = 0; i < H; i++)cin >> target[i].col[0] >> target[i].col[1] >> target[i].col[2];


	for (int i = 0; i < K - 1; i++) {
		for (int j = 0; j < K; j++) {
			Tube a;
			for (int k = 0; k < 3; k++)a.col[k] = (own[i].col[k] + own[j].col[k]) / 2.0;

			a.to_make = { i,j };

			own.push_back(a);
		}
	}


	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - 1; j++)cout << 0 << " ";
		cout << endl;
	}

	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < N; j++)cout << 0 << " ";
		cout << endl;
	}


	int cnt = 0;
	bool remain = false;
	Tube color;

	for (int i = 0; i < H; i++) {
		double m = 1000000000;
		int idx = -1;

		for (int j = 0; j < own.size(); j++) {//どれが一番(素の状態で)近いスコアを出せるか調べている
			double memo = cal_score(own[j], target[i]);
			if (memo < m) {
				m = memo;
				idx = j;
			}
		}

		if (!remain) {//ここは変わらない
			if (own[idx].to_make.first == -1) {
				cout << "1 1 1 " << idx << endl;
				cout << "2 1 1" << endl;
			}
			else {

				int u = own[idx].to_make.first, v = own[idx].to_make.second;

				cout << "1 1 1 " << u << endl;
				cout << "1 1 2 " << v << endl;
				cout << "2 1 1" << endl;
				//cout << "3 1 1" << endl;//(1,1)の絵の具を0にする

				remain = true;

				for (int k = 0; k < 3; k++)color.col[k] = (own[u].col[k] + own[v].col[k]) / 2.0;

			}
		}
		else {

			int can = -1;

			for (int j = 0; j < own.size(); j++) {
				Tube a;
				if (j < K)for (int k = 0; k < 3; k++)a.col[k] = (own[j].col[k] + color.col[k]) / 2;
				else {
					int u = own[j].to_make.first, v = own[j].to_make.second;
					for (int k = 0; k < 3; k++)a.col[k] = (own[u].col[k] + own[v].col[k] + color.col[k]) / 3;
				}

				if (cal_score(a, target[i]) < m) {
					m = cal_score(a, target[i]);
					can = j;
				}
			}

			if (can == -1) {
				cout << "3 1 1" << endl;//(1,1)の絵の具を0にする
				
				if (own[idx].to_make.first == -1) {
					cout << "1 1 1 " << idx << endl;
					cout << "2 1 1" << endl;
					remain = false;
				}
				else {

					int u = own[idx].to_make.first, v = own[idx].to_make.second;

					cout << "1 1 1 " << u << endl;
					cout << "1 1 2 " << v << endl;
					cout << "2 1 1" << endl;
					//cout << "3 1 1" << endl;//(1,1)の絵の具を0にする

					remain = true;

					for (int k = 0; k < 3; k++)color.col[k] = (own[u].col[k] + own[v].col[k]) / 2.0;

				}
				
			}
			else {
				if (own[can].to_make.first == -1) {
					cout << "1 1 1 " << can << endl;
					cout << "2 1 1" << endl;
					remain = true;

					for (int k = 0; k < 3; k++)color.col[k] = (own[can].col[k] + color.col[k]) / 2;
				}
				else {
					int u = own[can].to_make.first, v = own[can].to_make.second;
					cout << "1 1 1 " << u << endl;
					cout << "1 1 1 " << v << endl;
					cout << "2 1 1" << endl;
					cout << "3 1 1" << endl;

					remain = true;
					for (int k = 0; k < 3; k++)color.col[k] = (own[u].col[k] + own[v].col[k] + color.col[k]) / 3.0;
				}
			}
		}

	}
}
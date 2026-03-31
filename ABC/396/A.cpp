#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;
using ll = long long;

class SegTree {
public:
    vector<ll> dat;
    ll siz = 1;

    SegTree(ll n) {
        while (siz < n) siz *= 2;
        dat.resize(2 * siz, -LLONG_MAX / 2);
    }

    void update(int id, ll x) {
        id += siz;
        dat[id] = x;
        while (id > 1) {
            id /= 2;
            dat[id] = max(dat[2 * id], dat[2 * id + 1]);
        }
    }

    ll getmax(ll L, ll R, ll a, ll b, ll u) {
        if (b <= L || R <= a) return -LLONG_MAX / 2;
        if (L <= a && b <= R) return dat[u];

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

int main() {
	int N; cin >> N;
	vector<int> A(N);
	for (int i = 0; i < N; i++)cin >> A[i];
	bool ans = false;
	for (int i = 0; i < N - 2; i++) {
		if (A[i] == A[i + 1] && A[i + 1] == A[i + 2])ans = true;
	}

	cout << (ans ? "Yes" : "No");
}
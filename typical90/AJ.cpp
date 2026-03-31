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

using namespace std;
using ll = long long;

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
	int N, Q; cin >> N >> Q;
	vector<pair<ll, ll>> P(N);
	for (int i = 0; i < N; i++)cin >> P[i].first >> P[i].second;
	vector<ll> A(N), B(N);
	for (int i = 0; i < N; i++) {
		A[i] = P[i].first - P[i].second;
		B[i] = P[i].first + P[i].second;
	}

	vector<ll> C = A, D = B;

	sort(A.begin(), A.end());
	sort(B.begin(), B.end());

	ll MA = A[N - 1], mA = A[0], MB = B[N - 1], mB = B[0];

	for (int i = 0; i < Q; i++) {
		int q; cin >> q;
		q--;

		ll ans = -1;

		ans = max(ans, MA - C[q]);
		ans = max(ans, C[q] - mA);
		ans = max(ans, MB - D[q]);
		ans = max(ans, D[q] - mB);

		cout << ans << endl;
	}
}
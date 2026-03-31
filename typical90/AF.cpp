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
	int N; cin >> N;
	vector<vector<int>> A(N, vector<int>(N, 0));
	for (int i = 0; i < N; i++)for (int j = 0; j < N; j++) cin >> A[i][j];
	set<pair<int, int>> st;
	int M; cin >> M;
	for (int i = 0; i < M; i++) {
		int a, b; cin >> a >> b;
		a--;
		b--;
		st.insert({ a,b });
		st.insert({ b,a });
	}

	ll ans = 100000000000;
	vector<int> P(N);
	for (int i = 0; i < N; i++)P[i] = i;

	do {
		ll memo = 0;

		for (int i = 0; i < N - 1; i++) {
			if (st.count({ P[i],P[i + 1] })) {//仲悪いペアがあった場合
				memo = 1000000000000000;
				break;
			}

			memo += A[P[i]][i];
		}

		memo += A[P[N - 1]][N - 1];

		ans = min(ans, memo);

	} while (next_permutation(P.begin(), P.end()));

	cout << (ans >= 10000000000 ? -1 : ans) << endl;
}
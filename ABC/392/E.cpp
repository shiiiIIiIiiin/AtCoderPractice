#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <map>
#include <set>
#include <iterator>

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

class cable {
public:
	int a, b, id;

	cable(int x, int y, int i) {
		a = x;
		b = y;
		id = i;
	}
};

int main() {
	//なくても連結状態を保持できるケーブルがあるはずだからそれを調べる
	int N, M; cin >> N >> M;
	UnionFind uf(N + 1);
	vector<cable> amari;

	for (int i = 1; i <= M; i++) {
		int a, b; cin >> a >> b;
		if (!uf.same(a, b)) {
			uf.unite(a, b);
		}
		else {
			cable c(a, b, i);
			amari.push_back(c);
		}
	}


	//ここまででamariには余ったケーブルの情報が入れられている
	set<int> group;
	for (int i = 1; i <= N; i++)group.insert(uf.root(i));

	//groupには連結成分のリーダー情報を入れた

	cout << group.size() - 1 << endl;
	int K = group.size() - 1;
	
	
	for (int i = 0; i < K; i++) {
		//i＋１個目の余ったケーブルをつなぎ変える
		auto u = amari[i];
		int l1 = uf.root(u.a);//一個目のリーダー
		group.erase(l1);

		int l2 = *group.begin();//二個目のリーダーを適当に決める
		group.erase(l2);

		uf.unite(l1, l2);//二つのグループを統合する

		cout << u.id << " " << u.a << " " << l2 << endl;

		group.insert(uf.root(l1));
	}
}
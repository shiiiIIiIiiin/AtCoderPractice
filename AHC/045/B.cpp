//今の状態だとgroupの前からとってるけど、groupをできるだけ近くの点にするようにしておいた方がいいのでは？
/*　120行目からの
		if (L < 4)return;

		↑この処理が必要かどうかは要検討
*/

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

using namespace std;
using ll = long long;

ll N, M, Q, L, W;
const ll shikiiW = 1800;//アプローチを変えるWの閾値,500以上2500以下で変化させる

class Point {
public:
	ll x, y;

	void init(ll a, ll b, ll c, ll d) {
		x = (a + b) / 2;
		y = (c + d) / 2;
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
		if (rx == ry) return;

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

ll dist2(Point& a, Point& b) {//2点間の距離を計算する
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

ll com_score(vector<pair<int, int>>& p, vector<Point>& P) {//グラフの暫定スコアを計算する
	ll res = 0;
	for (int i = 0; i < p.size(); i++) {
		res += dist2(P[p[i].first], P[p[i].second]);
	}

	return res;
}

vector<int> search_aroundP(set<int>& remainP, ll& K, vector<pair<ll, int>>& D) {//中心点から近いK個の点を求める
	vector<pair<ll, int>> d = D;
	sort(d.begin(), d.end());

	vector<int> res;
	for (int i = 0; i < N; i++) {
		if (remainP.count(d[i].second)) {
			remainP.erase(d[i].second);
			res.push_back(d[i].second);

			if (res.size() == K)break;
		}
	}

	return res;
}

void change_min_tree(vector<int>& group, vector<pair<int, int>>& ans, vector<Point>& P, vector<vector<pair<ll, int>>>& d) {//与えられた点の集合について、占いを用いて可能な限り小さくなるように調整する、ただしWの値が大きい時のみ
	int n = group.size();

	if (n == 1)return;//多分何もしなくていい

	if (n <= L) {
		cout << "? " << n << " ";
		for (int j = 0; j < n; j++)cout << group[j] << " ";
		cout << endl;

		for (int j = 0; j < n - 1; j++) {
			int a, b; cin >> a >> b;
			ans[j] = { a,b };
		}
	}
	else {
		if (W < shikiiW)return;

		if (L <= 4)return;


		ans.clear();//一旦リセットする、groupの情報さえあればいい

		//groupの中身を近い順に並び変える
		int cnt = 0;
		bool f = true;
		vector<int> pre(0);
		set<int> remainP;
		for (int i = 0; i < group.size(); i++)remainP.insert(group[i]);

		while (true) {
			vector<int> q;
			//今の状態だとgroupの前からとってるけど、groupをできるだけ近くの点にするようにしておいた方がいいのでは？
				//q.push_back(group[cnt]);
				ll siz = min(L, ll(n - cnt));

				int center = -1;
				ll mind = LLONG_MAX / 2;

				for (int i = 0; i < group.size(); i++) {//一番x座標が小さいものを選ぶ
					if (remainP.count(group[i]) && mind > P[group[i]].x) {
						center = group[i];
						mind = P[group[i]].x;
					}
				}

				q = search_aroundP(remainP, siz, d[center]);

				if (siz == group.size() - cnt)f = false;
				cnt += L;
		//-------------------------↑ここまでqを決定する処理--------------------

			if (q.size() >= 2) {
				cout << "? " << q.size() << " ";
				for (auto x : q)cout << x << " ";
				cout << endl;
				cout.flush();
			}

			for (int i = 0; i < q.size() - 1; i++) {
				int a, b; cin >> a >> b;
				ans.push_back({ a,b });
			}

			if (pre.size() == 0) {
				pre = q;
				continue;
			}

			int mv = -9, mu = -9;
			ll md = LLONG_MAX / 2;//一番近い距離

			for (int i = 0; i < pre.size(); i++)for (int j = 0; j < q.size(); j++) {

				if (md > dist2(P[pre[i]], P[q[j]])) {
					mv = pre[i];
					mu = q[j];
				}
			}

			ans.push_back({ mu,mv });

			pre = q;

			if (!f)break;
		}
	}

}


int main() {
	cin >> N >> M >> Q >> L >> W;
	vector<ll> G(M);
	for (int i = 0; i < M; i++)cin >> G[i];

	//Wの値によってアプローチを変えるのがいいかもしれない

	vector<Point> P(N);

	for (int i = 0; i < N; i++) {
		int a, b, c, d; cin >> a >> b >> c >> d;
		P[i].init(a, b, c, d);
	}


	vector<vector<pair<ll, int>>> d(N, vector<pair<ll, int>>(N));//d[i][j]...点iから点jまでのチェビシェフ距離

	for (int i = 0; i < N; i++)for (int j = 0; j < N; j++) {//チェビシェフ距離を計算する
		d[i][j].first = max(labs(P[i].x - P[j].x), labs(P[i].y - P[j].y));
		d[i][j].second = j;
	}

	set<int> remainP;//まだ最小全域木を作らず残っている点の集合
	for (int i = 0; i < N; i++)remainP.insert(i);

	vector<vector<pair<int, int>>> ans(M);
	vector<pair<ll, int>> srt(M);
	vector<vector<int>> groups(M);

	for (int i = 0; i < M; i++) {
		srt[i].first = G[i];
		srt[i].second = i;
	}
	sort(srt.begin(), srt.end());
	reverse(srt.begin(), srt.end());

	for (int i = 0; i < M; i++) {
		int u = -1;//どの点を中心にするか考える
		ll mx = LLONG_MAX / 2;
		for (int i = 0; i < N; i++) {
			if (remainP.count(i)) {
				if (mx > P[i].x) {//左から順に消費していく
					u = i;
					mx = P[i].x;
				}
			}
		}

		if (u == -1)break;//もうグループは作らない←多分実行されない

		vector<int> group = search_aroundP(remainP, srt[i].first, d[u]);

		//groupの点でクラスカル法を実行して、最小全域木をつくり、出力する


		// クラスカル法で最小全域木を作成
		vector<pair<ll, pair<int, int>>> edges;
		for (int j = 0; j < group.size(); j++) {
			for (int k = j + 1; k < group.size(); k++) {
				int a = group[j], b = group[k];
				ll weight = dist2(P[a], P[b]);
				edges.push_back({ weight, {a, b} });
			}
		}

		sort(edges.begin(), edges.end()); // 辺を距離順にソート
		UnionFind uf(N);
		vector<pair<int, int>> mst;

		for (auto& e : edges) {
			ll w = e.first;
			int a = e.second.first, b = e.second.second;
			if (!uf.same(a, b)) {
				uf.unite(a, b);
				mst.push_back({ a, b });
			}
		}


		for (int j = 0; j < group.size(); j++)groups[srt[i].second].push_back(group[j]);
		for (int j = 0; j < mst.size(); j++)ans[srt[i].second].push_back({ mst[j].first,mst[j].second });
	}


	for (int i = 0; i < M; i++) {
		change_min_tree(groups[i], ans[i], P, d);
	}

	cout << "!" << endl;

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < groups[i].size(); j++)cout << groups[i][j] << " ";
		cout << endl;

		for (int j = 0; j < ans[i].size(); j++)cout << ans[i][j].first << " " << ans[i][j].second << endl;
	}

}
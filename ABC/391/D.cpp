#include<iostream>
#include<vector>
#include<queue>
#include<climits>
#include<algorithm>
#include<map>
#include<set>
using namespace std;
using ll = long long;

int main() {
	int N, W; cin >> N >> W;
	vector<vector<pair<ll, int>>> blocks(W+1);
	for (int i = 0; i < N; i++) {
		int x, y; cin >> x >> y;
		blocks[x].push_back({ y,i + 1 });
	}

	for (int i = 1; i <= W; i++)sort(blocks[i].begin(), blocks[i].end());

	size_t cnt = 1000000000;

	for (int i = 1; i <= W; i++)cnt = min(cnt, blocks[i].size());

	vector<ll> dis(N + 1,1000000000000);

	ll pre = 0;

	for (int i = 0; i < cnt; i++) {//グループiが消えるタイミングを知りたい
		ll u = -1;
		for (int j = 1; j <= W; j++)u = max(u, blocks[j][i].first);

		for(int j=1;j<=W;j++)dis[blocks[j][i].second] = max(pre + 1, u);

		pre = max(pre + 1, u);
	}

	//クエリに答える部分

	int Q; cin >> Q;

	for (int i = 0; i < Q; i++) {
		int t, a; cin >> t >> a;
		cout << (dis[a] <= t ? "No" : "Yes") << endl;
	}

}
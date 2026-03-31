#include<iostream>
#include<vector>
#include<queue>
#include<climits>
#include<algorithm>
using namespace std;

int dfs(vector<int>& cnt, vector<vector<int>>& G, int pos, int pre) {
	for (int i = 0; i < G[pos].size(); i++) {
		int nex = G[pos][i];
		if (nex == pre)continue;
		cnt[pos]+=dfs(cnt,G,nex,pos)+1;
	}

	return cnt[pos];
}

int main() {
	int N; cin >> N;
	vector<vector<int>> G(N + 1);
	for (int i = 0; i < N - 1; i++) {
		int u, v; cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	if (G[1].size() == 1) {
		cout << 1 << endl;
		return 0;
	}

	vector<int> cnt(N + 1, 0);//自分より下に子孫が何人いるか調べる

	dfs(cnt, G, 1, -1);

	int ans = 0;
	vector<int> memo;
	for (int i = 0; i < G[1].size(); i++)memo.push_back(cnt[G[1][i]]);
	sort(memo.begin(), memo.end());
	for (int i = 0; i < G[1].size() - 1; i++)ans += memo[i]+1;
	//for (int i = 1; i <= N; i++)cout << cnt[i] << " ";

	cout << ans + 1 << endl;


}
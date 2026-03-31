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

using namespace std;
using ll = long long;

void dfs(int N, vector<vector<int>>& G, vector<int>& X, vector<vector<int>>& bests,int pos,int pre) {
	//自分の子と自分自身のbest20をbests[pos]に格納する
	vector<int> memo;

	for (int i = 0; i < G[pos].size(); i++) {
		int nex = G[pos][i];
		if (nex == pre)continue;

		dfs(N, G, X, bests, nex, pos);

		for (auto x : bests[nex])memo.push_back(x);//子の上位候補をmemoに加える
	}
	
	memo.push_back(X[pos]);//自分自身を加える
	sort(memo.begin(), memo.end());

	for (int i = 0; i < 20; i++) {//上位20位まで取り出す
		if (i >= memo.size())break;//子の数が20以下なら飛ばす
		bests[pos].push_back(memo[memo.size() - 1 - i]);
	}

}

int main() {
	int N, Q; cin >> N >> Q;
	vector<vector<int>> G(N + 1);
	vector<int> X(N + 1);
	for (int i = 1; i <= N; i++)cin >> X[i];
	for (int i = 0; i < N - 1; i++) {
		int a, b; cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}

	vector<vector<int>> bests(N + 1);

	dfs(N, G, X, bests, 1, -1);

	for (int i = 0; i < Q; i++) {
		int v, k; cin >> v >> k;
		cout << bests[v][k - 1] << endl;
	}
}
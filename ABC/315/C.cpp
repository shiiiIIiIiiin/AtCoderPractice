#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <map>
#include <set>
#include <iterator>
#include <unordered_map>

using namespace std;
using ll = long long;

int main() {
	int N; cin >> N;
	vector<vector<ll>> ice(N+1);
	for (int i = 0; i < N; i++) {
		int f, s; cin >> f >> s;
		ice[f].push_back(s);
	}

	for (int i = 0; i < N + 1; i++)sort(ice[i].begin(), ice[i].end());

	ll ans = -1;

	//一つアイスを決める、もう一つも決める

	for (int i = 1; i <= N; i++) {//同じアイスを選ぶ場合
		if (ice[i].size() <= 1)continue;
		int n = ice[i].size()-1;
		ans = max(ans, ice[i][n] + ice[i][n - 1]/2);
	}

	vector<ll> MAXS;
	for (int i = 1; i <= N; i++) {
		if (ice[i].size() == 0)continue;
		MAXS.push_back(ice[i][ice[i].size() - 1]);
	}

	sort(MAXS.begin(), MAXS.end());

	if (MAXS.size() >= 2)ans = max(ans, MAXS[MAXS.size() - 1] + MAXS[MAXS.size() - 2] );

	cout << ans << endl;
}
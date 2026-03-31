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
	int N, M; cin >> N >> M;
	vector<bool> m(N+1,false);
	for (int i = 0; i < N; i++) {
		int a; cin >> a;
		m[a] = true;
	}

	vector<int> ans;
	for (int i = 1; i <= N; i++)if (!m[i])ans.push_back(i);

	cout << ans.size() << endl;
	for (auto x : ans)cout << x << " ";
}
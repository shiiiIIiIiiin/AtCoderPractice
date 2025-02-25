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

int main() {
	int N, M; cin >> N >> M;
	int ans = 0;

	set<pair<int, int>> s;

	for (int i = 0; i < M; i++) {
		int u, v; cin >> u >> v;
		if (u == v) {
			ans++;
			continue;
		}

		if (s.count({ u,v }))ans++;
		
		s.insert({ u,v });
		s.insert({ v,u });

	}

	cout << ans << endl;
}

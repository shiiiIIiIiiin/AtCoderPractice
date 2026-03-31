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

void dfs(vector<vector<ll>>& A, set<int>& s, vector<bool>& visited, int pos) {
	visited[pos] = true;
	s.insert(pos);

	for (int i = 0; i < A[pos].size(); i++) {
		int nex = A[pos][i];
		if (visited[nex])continue;
		dfs(A, s, visited, nex);
	}

	return;
}

int main() {
	int N; cin >> N;
	vector<ll> T(N + 1), K(N + 1);
	vector<vector<ll>> A(N + 1);

	for (int i = 1; i <= N; i++) {
		cin >> T[i] >> K[i];
		for (int j = 0; j < K[i]; j++) {
			ll a; cin >> a;
			A[i].push_back(a);
		}
	}

	set<int> memo;//修練しないといけない技をすべて書き出す
	vector<bool> visited(N + 1, false);
	dfs(A, memo, visited, N);
	
	ll ans = 0;

	for (auto x : memo)ans += T[x];

	cout << ans << endl;
}
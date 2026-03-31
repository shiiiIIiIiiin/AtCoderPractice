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

void dfs(ll &N, ll &X, vector<ll>& L, vector<vector<ll>>& a,ll pos,ll cnt,ll &ans) {
	if (pos == N && cnt == X)ans++;
	if (pos == N)return;
	
	for (int i = 0; i < a[pos].size(); i++) {
		if (cnt > X / a[pos][i])continue;
		dfs(N, X, L, a, pos + 1, cnt * a[pos][i], ans);
	}


}

int main() {
	ll N, X; cin >> N >> X;
	vector<ll> L(N);
	vector<vector<ll>> a(N);

	for (int i = 0; i < N; i++) {
		cin >> L[i];
		for (int j = 0; j < L[i]; j++) {
			ll u; cin >> u;
			a[i].push_back(u);
		}
	}

	ll ans = 0;

	dfs(N, X, L, a, 0, 1, ans);

	cout << ans << endl;
}
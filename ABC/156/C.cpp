#include<iostream>
#include<vector>
#include<queue>
#include<climits>
#include<algorithm>
#include<map>
#include<set>
using namespace std;
using ll = long long;

ll f(ll x) {
	return x * x;
}

int main() {
	int N; cin >> N;
	vector<int> X(N);
	for (int i = 0; i < N; i++)cin >> X[i];

	ll ans = LLONG_MAX;

	for (int p = -100; p <= 100; p++) {
		ll memo = 0;
		for (int i = 0; i < N; i++)memo += f(p - X[i]);

		ans = min(ans, memo);
	}

	cout << ans << endl;
}
#include<iostream>
#include<vector>
#include<queue>
#include<climits>
#include<algorithm>
using namespace std;
using ll = long long;

void solve(vector<ll>& A, ll k) {
	ll l = -1, r = 2e18,m;

	int id=-102321;
	while (r - l > 1) {
		m = (r + l) / 2;
		ll id = lower_bound(A.begin(), A.end(), m)-A.begin();

		if (m - id > k)r = m;
		else l = m;
	}
	cout << l << endl;
	//cout << id << endl;
}

int main() {
	ll N, Q; cin >> N >> Q;
	vector<ll> A(N);
	for (int i = 0; i < N; i++)cin >> A[i];

	for (int i = 0; i < Q; i++) {
		ll k; cin >> k;
		solve(A, k);
	}
}
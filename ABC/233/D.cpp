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
	ll N, K; cin >> N >> K;
	vector<ll> A(N+1);
	for (int i = 1; i <= N; i++)cin >> A[i];
	A[0] = 0;
	
	for (int i = 0; i < N; i++)A[i + 1] += A[i];


	map<ll,ll> m;
	ll ans = 0;

	for (int r = 1; r <= N; r++) {
		m[A[r-1]]++;
		ans += m[A[r] - K];
	}

	cout << ans << endl;
}
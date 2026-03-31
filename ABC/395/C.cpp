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

int main() {
	int N; cin >> N;
	vector<int> A(N);
	for (int i = 0; i < N; i++)cin >> A[i];
	map<int, vector<ll>> mp;

	for (int i = 0; i < N; i++) {
		mp[A[i]].push_back(i);
	}

	ll ans = LLONG_MAX / 2;

	for (auto l : mp) {
		ll memo = LLONG_MAX / 2;

		for (int i = 0; i < l.second.size()-1; i++) {
			memo = min(memo, l.second[i + 1] - l.second[i] + 1);
		}

		ans = min(ans, memo);
	}

	cout << (ans == LLONG_MAX / 2 ? -1 : ans) << endl;
}
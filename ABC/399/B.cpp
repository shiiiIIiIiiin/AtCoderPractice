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
#include <deque>

using namespace std;
using ll = long long;

int main() {
	int N; cin >> N;
	vector<pair<int, int>> P(N);
	for (int i = 0; i < N; i++) {
		cin >> P[i].first;
		P[i].second = i + 1;
	}

	sort(P.rbegin(), P.rend());

	int r = 1, cnt = 0;
	vector<int> ans(N + 1, -1);

	ans[P[0].second] = 1;

	for (int i = 1; i < N; i++) {
		if (P[i - 1].first == P[i].first) {
			cnt++;
			ans[P[i].second] = r;
		}
		else {
			r += cnt + 1;
			cnt = 0;
			ans[P[i].second] = r;
		}
	}

	for (int i = 1; i <= N; i++)cout << ans[i] << endl;
}
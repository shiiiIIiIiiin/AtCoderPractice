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

bool check(int i, int j) {
	int x = i % 10;

	bool res = true;

	while (i != 0) {
		if (i % 10 != x)res = false;
		i /= 10;
	}

	while (j != 0) {
		if (j % 10 != x)res = false;
		j /= 10;
	}

	return res;
}

int main() {
	int N; cin >> N;
	vector<int> D(N);
	for (int i = 0; i < N; i++)cin >> D[i];

	ll ans = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 1; j <= D[i]; j++) {
			if (check(i + 1, j))ans++;
		}
	}

	cout << ans << endl;
}
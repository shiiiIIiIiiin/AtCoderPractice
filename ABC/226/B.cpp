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
	vector<vector<int>> a(N);
	for (int i = 0; i < N; i++) {
		int L; cin >> L;
		for (int j = 0; j < L; j++) {
			int k; cin >> k;
			a[i].push_back(k);
		}
	}

	set<vector<int>> s;
	for (int i = 0; i < N; i++)s.insert(a[i]);

	cout << s.size();

}
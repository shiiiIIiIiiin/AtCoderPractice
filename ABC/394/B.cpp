#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <map>
#include <set>
#include <iterator>
#include <unordered_map>

using namespace std;
using ll = long long;

int main() {
	int N; cin >> N;
	vector<pair<int, string>> P(N);
	for (int i = 0; i < N; i++) {
		string s; cin >> s;
		P[i].first = s.size();
		P[i].second = s;
	}

	sort(P.begin(), P.end());

	for (int i = 0; i < N; i++)cout << P[i].second;
}

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
	bool ans = true;

	for (int i = 0; i < N-1; i++)if (A[i] >= A[i + 1])ans = false;

	cout << (ans ? "Yes" : "No");
}
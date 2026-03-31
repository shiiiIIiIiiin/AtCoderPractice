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
	vector<int> A(3);
	for (int i = 0; i < 3; i++)cin >> A[i];
	sort(A.begin(), A.end());

	cout << (A[2] == A[1] * A[0] ? "Yes" : "No");
}
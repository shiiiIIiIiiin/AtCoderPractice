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
	int N, K; cin >> N >> K;
	vector<int> A(N), B(N);
	for (int i = 0; i < N; i++)cin >> A[i] >> B[i];

	vector<int> P(2 * N);
	for (int i = 0; i < N; i++) {
		P[2 * i] = B[i];
		P[2 * i + 1] = A[i] - B[i];
	}

	sort(P.begin(), P.end());

	ll ans = 0;

	for (int i = 0; i < K; i++)ans += P[P.size() - 1 - i];
	cout << ans << endl;
}
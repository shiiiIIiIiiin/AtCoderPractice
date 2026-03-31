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
	int N, X; cin >> N >> X;
	vector<int> S(N);
	for (int i = 0; i < N; i++)cin >> S[i];

	ll ans = 0;
	for (int i = 0; i < N; i++)if (S[i] <= X)ans += S[i];
	cout << ans << endl;

}
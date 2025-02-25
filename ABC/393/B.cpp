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
	string S; cin >> S;
	int N = S.size();
	ll ans = 0;
	for (int i = 0; i < N - 2; i++)for (int j = i + 1; j < N - 1; j++)for (int k = j + 1; k < N; k++) {
		if (S[i] == 'A' && S[j] == 'B' && S[k] == 'C' && j - i == k - j)ans++;
	}
	cout << ans << endl;
}

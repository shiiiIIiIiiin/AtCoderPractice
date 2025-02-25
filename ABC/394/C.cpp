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
	string S; cin >> S;
	int N = S.size();
	for (int i = N-1; i >= 0; i--) {
		if (i == 0)continue;
		if (S[i] == 'A' && S[i - 1] == 'W') {
			S[i - 1] = 'A';
			S[i] = 'C';
		}
	}

	cout << S << endl;
}

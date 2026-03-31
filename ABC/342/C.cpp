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
	string S; cin >> S;
	int Q; cin >> Q;

	string t = "abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < Q; i++) {
		char c, d; cin >> c >> d;

		for (int j = 0; j < t.size(); j++) {
			if (t[j] == c)t[j] = d;
		}
	}

	for (int i = 0; i < N; i++) {
		S[i] = t[S[i] - 'a'];
	}

	cout << S << endl;
}
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
	vector<string> S(N+1);

	string t = "";
	for (int i = 0; i <= N; i++)t += '_';
	for (int i = 0; i <= N; i++)S[i] = t;

	for (int i = 1; i <= N; i++) {
		int j = N + 1 - i;
		if (i <= j) {
			if (i % 2 == 1) {
				for (int a = i; a <= j; a++) {
					for (int b = i; b <= j; b++) {
						S[a][b] = '#';
					}
				}
			}
			else {
				for (int a = i; a <= j; a++) {
					for (int b = i; b <= j; b++) {
						S[a][b] = '.';
					}
				}
			}

		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << S[i][j];
		}
		cout << endl;
	}
}
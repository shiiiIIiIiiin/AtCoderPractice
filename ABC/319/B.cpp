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
	string ans = "";

	for (int i = 0; i <= N; i++) {
		for (int j = 1; j <= 10; j++) {
			if (j == 10) {
				ans += '-';
				break;
			}
			if (N % j != 0 || i % (N / j) != 0)continue;
			else {
				ans += '0' + j;
				break;
			}

		}
	}

	cout << ans << endl;
}
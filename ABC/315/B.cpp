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
	int M; cin >> M;
	vector<int> D(M);
	for (auto& i : D)cin >> i;
	
	int sum = 0;
	for (auto x : D)sum += x;

	sum = (sum + 1) / 2;
	int cnt = 0;

	for (int i = 0; i < M; i++) {
		for (int j = 1; j <= D[i]; j++) {
			cnt++;
			if (cnt == sum) {
				cout << i + 1 << " " << j;
				return 0;
			}
		}
	}
	
}
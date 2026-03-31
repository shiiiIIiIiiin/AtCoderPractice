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

using namespace std;
using ll = long long;

int main() {
	int N, M; cin >> N >> M;
	vector<int> A(M);
	for (int i = 0; i < M; i++)cin >> A[i];

	vector<bool> re(N + 1, false);
	for (int i = 0; i < M; i++)re[A[i]] = true;

	vector<int> ans;
	int cnt = 0;
	for (int i = 1; i <= N; i+=cnt + 1) {
		cnt = 0;
		while (re[i + cnt])cnt++;
		for (int j = 0; j <= cnt; j++)ans.push_back(i + cnt - j);
	}

	for (auto x : ans)cout << x << " ";
}
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

int kouyakusu(int x, int y) {
	if (y == 0)return x;
	return kouyakusu(y, x % y);
}

int main() {
	int N; cin >> N;
	//全ての街の移動を考える

	set<pair<int, int>> s;

	vector<int> x(N), y(N);
	for (int i = 0; i < N; i++)cin >> x[i] >> y[i];

	for (int i = 0; i < N - 1; i++)for (int j = i + 1; j < N; j++) {//街iと街jを行き来するのに覚える魔法
		int dx = x[j] - x[i], dy = y[j] - y[i];
		int d = kouyakusu(max(abs(dx), abs(dy)), min(abs(dx), abs(dy)));
		dx /= d;
		dy /= d;

		s.insert({ dx,dy });
		s.insert({ -dx,-dy });

	}

	cout << s.size();
}
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
	int x, y; cin >> x >> y;

	cout << max(0, (y - x + 9) / 10);
}
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
	int l, r; cin >> l >> r;
	string s; cin >> s;

	reverse(s.begin() + l - 1, s.begin() + r);

	cout << s;
}
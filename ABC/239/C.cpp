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
	ll x1, x2, y1, y2; cin >> x1 >> y1 >> x2 >> y2;
	
	vector<pair<ll, ll>> d = { {2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1} };

	set<pair<ll, ll>> st;

	for (int i = 0; i < 8; i++)for (int j = i ; j < 8; j++) {
		ll a = labs(d[i].first + d[j].first), b = labs(d[i].second + d[j].second);
		st.insert({ a,b });
		
	}

	cout << (st.count({ labs(x1 - x2),labs(y1 - y2) }) ? "Yes" : "No");
}
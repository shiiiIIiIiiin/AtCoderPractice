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
	double H; cin >> H;
	double ans = sqrt(H * (12800000 + H));

	cout << fixed << setprecision(8) << ans << endl;
}
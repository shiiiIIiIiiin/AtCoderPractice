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
#include <deque>

using namespace std;
using ll = long long;

int main() {
	int N; cin >> N;
	string S, T; cin >> S >> T;
	int ans = 0;
	for (int i = 0; i < N; i++)if (S[i] != T[i])ans++;
	cout << ans << endl;
}
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
	string S, T; cin >> S >> T;
	if (S[0] == 's' && T[0] == 'f')cout << 2 << endl;
	if (S[0] == 's' && T[0] == 's')cout << 1 << endl;
	if (S[0] == 'f' && T[0] == 'f')cout << 4 << endl;
	if (S[0] == 'f' && T[0] == 's')cout << 3 << endl;


}

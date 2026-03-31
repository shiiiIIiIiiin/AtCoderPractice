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

int main() {
	string S; cin >> S;
	int k = 0;
	int i = 0;
	while (S[i] != '.') {
		k *= 10;
		k += S[i] - '0';
		i++;
	}
	cout << ((S[S.size()-3] - '0') >= 5 ? k + 1 : k);
}
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
	ll X; cin >> X;
	ll cnt = 1;
	for (int i = 1; i <= X; i++) {
		cnt *= i;
		if (cnt == X) {
			cout << i;
			return 0;
		}
	}
}
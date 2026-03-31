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
	int Q; cin >> Q;
	ll cnt = 0;
	vector<ll> hebi;
	hebi.push_back(0);

	for (int i = 0; i < Q; i++) {
		int type; cin >> type;

		if (type == 1) {
			ll l; cin >> l;
			hebi.push_back(hebi[hebi.size()-1]+l);
		}
		else if (type == 2) {
			cnt++;
		}
		else {
			ll k; cin >> k;
			cout << hebi[cnt + k - 1] - hebi[cnt] << endl;
		}
	}
}
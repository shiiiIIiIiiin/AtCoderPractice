#include<iostream>
#include<vector>
#include<queue>
#include<climits>
#include<algorithm>
#include<map>
#include<set>
using namespace std;
using ll = long long;

int main() {
	int N, Q; cin >> N >> Q;
	set<int> s;
	vector<int> cnt(N + 1, 1);
	vector<int> u(N + 1);
	for (int i = 1; i <= N; i++)u[i] = i;


	for (int i = 0; i < Q; i++) {
		int c; cin >> c;

		if (c == 1) {
			int p, h; cin >> p >> h;
			cnt[u[p]]--;
			cnt[h]++;

			if (cnt[u[p]] == 1)s.erase(u[p]);
			if (cnt[h] >= 2)s.insert(h);
			u[p] = h;
		}
		else {
			cout << s.size() << endl;
		}
	}
}
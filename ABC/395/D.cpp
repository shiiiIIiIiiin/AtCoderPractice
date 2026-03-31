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
	int N, Q; cin >> N >> Q;
	vector<int> pos(N + 1), atukai(N + 1),inv(N+1);
	for (int i = 1; i <= N; i++) {
		pos[i] = i;
		atukai[i] = i;
		inv[i]=i;
	}

	for (int i = 0; i < Q; i++) {
		int op; cin >> op;

		if (op == 1) {
			int a, b; cin >> a >> b;
			pos[a] = inv[b];
		}
		else if (op == 2) {
			int a, b; cin >> a >> b;
			int ma=atukai[inv[a]],mb=atukai[inv[b]];
			
			swap(atukai[inv[a]],atukai[inv[b]]);//巣aとして扱われているものと巣ｂとして扱われているものの名前を入れ替える
			
			swap(inv[ma],inv[mb]);
			
		}
		else {
			int a; cin >> a;
			cout << atukai[pos[a]] << endl;
		}
	}

}
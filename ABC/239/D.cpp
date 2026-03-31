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
	ll A, B, C, D; cin >> A >> B >> C >> D;
	//200以下の素数の集合を作る
	set<ll> st;
	vector<bool> sosu(201, false);

	for (int i = 2; i <= 200; i++) {
		if (!sosu[i]) {
			sosu[i] = true;
			st.insert(i);
			for (int j = i; j <= 200; j += i)sosu[j] = true;
		}

	}

	
	bool ans = false;//trueの場合Takahashiの勝ち

	for (int i = A; i <= B; i++) {
		bool exist = false;
		for (int j = C; j <= D; j++) if (st.count(i + j))exist = true;

		if (!exist)ans = true;
	}

	cout << (ans ? "Takahashi" : "Aoki");
	

	
}
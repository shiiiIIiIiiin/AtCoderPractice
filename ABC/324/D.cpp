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
#include <math.h>

using namespace std;
using ll = long long;


int main() {
	int N; cin >> N;
	string S; cin >> S;
	map<string,ll> mp;

	for (ll i = 0; i * i <= pow(10, N); i++) {
		string t = "";
		ll k = i * i;

		t += to_string(k);
		int cnt = t.size();

		for (int j = 0; j < N - cnt; j++)t += '0';

		sort(t.begin(), t.end());

		mp[t]++;
	}

	sort(S.begin(), S.end());

	cout << mp[S] << endl;
}
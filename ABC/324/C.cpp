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

bool check1(string& T, string& S) {
	int ct = 0, cs = 0, cnt = 0;
	if (T.size() != S.size() + 1)return false;
	while (true) {
		if (ct >= T.size() || cs >= S.size()) {
			if (ct == T.size() && cs == S.size())return true;
			if (ct == T.size() - 1 && cs == S.size())return true;
			return false;
		}

		if (T[ct] != S[cs]) {
			if (cnt >= 1)return false;
			ct++;
			cnt++;
			continue;
		}

		ct++;
		cs++;
	}
}

bool check2(string& T, string& S) {
	int ct = 0, cs = 0, cnt = 0;
	if (S.size() != T.size() + 1)return false;
	while (true) {
		if (ct >= T.size() || cs >= S.size()) {
			if (ct == T.size() && cs == S.size())return true;
			if (ct == T.size() && cs == S.size() - 1)return true;
			return false;
		}

		if (T[ct] != S[cs]) {
			if (cnt >= 1)return false;
			cs++;
			cnt++;
			continue;
		}

		ct++;
		cs++;
	}
}

bool check3(string& T, string& S) {
	if (T.size() != S.size())return false;
	int cnt = 0;

	for (int i = 0; i < S.size(); i++) {
		if (T[i] != S[i])cnt++;
	}

	if (cnt == 1)return true;

	return false;
}

int main() {
	int N; cin >> N;
	string T; cin >> T;
	vector<string> S(N);
	for (int i = 0; i < N; i++)cin >> S[i];

	vector<int> ans;

	for (int i = 0; i < N; i++) {
		bool flag = false;
		if (S[i] == T)flag = true;

		if (check1(T, S[i]))flag = true;
		if (check2(T, S[i]))flag = true;
		if (check3(T, S[i]))flag = true;

		if (flag)ans.push_back(i + 1);
	}

	cout << ans.size() << endl;
	for (auto s : ans)cout << s << " ";

}
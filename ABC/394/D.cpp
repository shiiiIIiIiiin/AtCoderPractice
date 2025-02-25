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

bool check(string &S) {
	stack<char> s;
	int N = S.size();

	for (int i = 0; i < N; i++) {
		char c = S[i];

		if (c == '(' || c == '[' || c == '<')s.push(c);
		else {
			if (s.empty())return false;
			char c2 = s.top(); s.pop();

			if (!((c == ')' && c2 == '(') || (c == ']' && c2 == '[') || (c == '>' && c2 == '<')))return false;
		}


	}

	return s.empty();
}

int main() {
	string S; cin >> S;
	int N = S.size();
	
	cout << (check(S) ? "Yes" : "No");
}

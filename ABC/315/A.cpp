#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <map>
#include <set>
#include <iterator>
#include <unordered_map>

using namespace std;
using ll = long long;

int main() {
	string S,t="aiueo"; cin >> S;
	set<char> st;
	for (auto c : t)st.insert(c);
	for (int i = 0; i < S.size(); i++)if (!st.count(S[i]))cout << S[i];
}
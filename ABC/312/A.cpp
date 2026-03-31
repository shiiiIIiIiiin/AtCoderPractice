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
	string S; cin >> S;
	set<string> st;

	st.insert("ACE");
	st.insert("BDF");
	st.insert("CEG");
	st.insert("DFA");
	st.insert("EGB");
	st.insert("FAC");
	st.insert("GBD");

	cout << (st.count(S) ? "Yes" : "No") << endl;
}
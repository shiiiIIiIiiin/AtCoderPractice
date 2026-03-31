#include<iostream>
#include<vector>
#include<queue>
#include<climits>
using namespace std;
using ll = long long;

int main() {
	string S; cin >> S;
	int cnt = 0;
	for (int i = 0; i < S.size(); i++) {
		if (S[i] != cnt + 'A')cnt++;
		if (S[i] != cnt + 'A')cnt++;
		if (S[i] != cnt + 'A') {
			cout << "No";
			return 0;
		}
	}

	cout << "Yes";
}
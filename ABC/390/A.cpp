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
	vector<int> A(5);
	for (int i = 0; i < 5; i++)cin >> A[i];

	vector<bool> suc(5, false);

	for (int i = 0; i < 5; i++)if (A[i] == i + 1)suc[i] = true;


	int cnt = 0;
	for (int i = 0; i < 4; i++)if (!suc[i] && !suc[i + 1]) cnt++;

	if (cnt == 1) cout << "Yes";
	else cout << "No";
	return 0;
}
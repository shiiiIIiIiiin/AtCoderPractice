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
	int N; cin >> N;
	vector<int> P(N);
	for (int i = 0; i < N; i++)cin >> P[i];
	int M = -1,id=-1;
	for (int i = 0; i < N; i++) {
		if(M<=P[i])M = P[i], id = i;
	}

	cout << (id == 0 ? 0: M - P[0] + 1);
}
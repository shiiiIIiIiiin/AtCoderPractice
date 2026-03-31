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
	int N, M; cin >> N >> M;
	vector<int> A(M), B(M);
	for (int i = 0; i < M; i++)cin >> A[i] >> B[i];

	int cnt = 0, memo = -1;

	for (int i = 1; i <= N; i++) {
		bool can = true;
		for (int j = 0; j < M; j++) if (B[j] == i)can = false;
		if (can)cnt++, memo = i;
	}

	cout << (cnt > 1 || memo == -1 ? -1 : memo);
}
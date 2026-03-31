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
	vector<ll> A(N);
	for (int i = 0; i < N; i++)cin >> A[i];

	for (int i = 0; i < N - 1; i++) if (A[1] * A[i] != A[i + 1] * A[0]) {
		cout << "No";
		return 0;
	}

	cout << "Yes";
}
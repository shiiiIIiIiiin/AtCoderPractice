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
	ll N, K; cin >> N >> K;
	vector<ll> A(N), B(N);
	for (int i = 0; i < N; i++)cin >> A[i];
	for (int i = 0; i < N; i++)cin >> B[i];

	ll cnt = 0;

	for (int i = 0; i < N; i++)cnt += labs(A[i] - B[i]);

	cout << (cnt <= K && (cnt - K) % 2 == 0 ? "Yes" : "No");
}
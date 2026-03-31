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
	ll N; cin >> N;
	vector<ll> A(N);
	for (int i = 0; i < N; i++)cin >> A[i];

	ll ans = 0, ans2 = 0, sum = 0;

	for (int i = 0; i < N; i++)sum += A[i];

	ll ave = sum / N, ave2 = (sum + N - 1) / N;

	for (int i = 0; i < N; i++) {
		if (ave - A[i] >= 0)ans += ave - A[i];
		else ans2 += A[i] - ave2;
	}
	
	cout << max(ans,ans2) << endl;
}
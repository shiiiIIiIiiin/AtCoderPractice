#include<iostream>
#include<vector>
#include<queue>
#include<climits>
using namespace std;
using ll = long long;

int main() {
	ll N; cin >> N;
	N--;
	vector<int> memo;

	while (N != 0) {
		memo.push_back(N % 5);
		N /= 5;
	}

	ll ans = 0;
	for (int i = 0; i < memo.size(); i++) {
		ans *= 10;
		ans += memo[memo.size() - 1 - i] * 2;
	}

	cout << ans ;
}
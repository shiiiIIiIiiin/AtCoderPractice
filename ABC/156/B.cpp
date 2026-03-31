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

	int ans = 0;

	while (N != 0) {
		ans++;
		N /= K;
	}

	cout << ans << endl;
}
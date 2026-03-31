#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <map>
#include <set>
#include <iterator>
#include <unordered_map>
#include <stack>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;
using ll = long long;

int main() {
	ll N, M; cin >> N >> M;
	vector<ll> B(N), W(M);
	for (int i = 0; i < N; i++)cin >> B[i];
	for (int i = 0; i < M; i++)cin >> W[i];

	ll ans = 0;
	sort(B.begin(), B.end(), greater<ll>());
	sort(W.begin(), W.end(), greater<ll>());

	int cw = 0, cb = 0;
	for (int i = 0; i < N; i++)if (B[i] >= 0)cb++;
	for (int i = 0; i < M; i++)if (W[i] > 0)cw++;

	if (cb >= cw) {
		for (int i = 0; i < cb; i++)ans += B[i];
		for (int i = 0; i < cw; i++)ans += W[i];
	}
	else {
		for (int i = 0; i < cw; i++) {
			if (i >= N)break;

			if (B[i] + W[i] > 0)ans += B[i] + W[i];
		}
	}

	cout << ans << endl;
}
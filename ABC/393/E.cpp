#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <map>
#include <set>
#include <iterator>
#include <unordered_map>

using namespace std;
using ll = long long;

void search_div(set<ll>& memo, ll X) {
	for (int i = 1; i * i <= X; i++) {
		if (X % i == 0) {
			memo.insert(i);
			memo.insert(X / i);
		}
	}

}

int main() {
	ll N, K; cin >> N >> K;
	vector<ll> A(N);
	for (int i = 0; i < N; i++)cin >> A[i];

	ll M = -1;//Aの要素の最大値
	for (int i = 0; i < N; i++)M = max(M, A[i]);

	vector<ll> cnt(M + 1, 0);//cnt[k]...Aの中にkが何個含まれるか
	for (int i = 0; i < N; i++)cnt[A[i]]++;
	vector<ll> div(M + 1, 0);//div[k]...Aの中にkの倍数がいくつあるか

	for (int i = 1; i <= M; i++) {
		for (int j = i; j <= M; j += i) {
			div[i] += cnt[j];
		}
	}

	/*
	for (int i = 0; i < N; i++) {
		set<ll> memo;
		search_div(memo, A[i]);

		for (auto x : memo) {
			if (div[A[i] / x] >= K) {
				cout << A[i] / x << endl;
				break;
			}
		}

	}
	*/


	vector<ll> u(M + 1, -1);

	for (ll d = 1; d <= M; d++) {
		if (div[d] < K) continue;
		for (int n = d; n <= M; n += d) {
			u[n] =  d;
		}
	}


	for (auto x : A)cout << u[x] << endl;
}

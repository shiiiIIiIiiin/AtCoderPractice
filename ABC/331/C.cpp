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
	int N; cin >> N;
	vector<pair<ll,int>> A(N);
	for (int i = 0; i < N; i++) {
		cin >> A[i].first;
		A[i].second = i;
	}

	sort(A.begin(), A.end());
	ll sum = 0;
	vector<ll> ans(N);
	ll memo = 0;
	
	for (int i = N - 1; i >= 0; i--) {
		ans[A[i].second] = sum;
		
		if (i - 1 >= 0 && A[i].first != A[i-1].first) {
			sum += memo + A[i].first;
			memo = 0;
		}
		else {
			memo += A[i].first;
		}
	}

	for (int i = 0; i < N; i++)cout << ans[i] << " ";
}
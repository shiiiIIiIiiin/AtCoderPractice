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
	int K = 15;
	vector<ll> repnit;
	ll cnt = 0;
	for (int i = 0; i < K; i++) {
		cnt *= 10;
		cnt++;

		repnit.push_back(cnt);
	}

	vector<ll> kouho;
	set<ll> st;
	for (int i = 0; i < K; i++)for (int j = 0; j < K; j++)for (int k = 0; k < K; k++) {
		st.insert(repnit[i] + repnit[j] + repnit[k]);
	}
	for (auto x : st) {
		kouho.push_back(x);
		//cout << x << endl;
	}

	cout << kouho[N - 1] << endl;
}
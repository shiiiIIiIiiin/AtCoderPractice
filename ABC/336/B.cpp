#include<iostream>
#include<vector>
using namespace std;

int main() {
	long long N; cin >> N;

	vector<int> ans;

	while (N != 0) {
		ans.push_back(N % 2);
		N /= 2;
	}

	int cnt = 0;
	for (int i = 0; i < ans.size(); i++) {
		if (ans[i] == 0)cnt++;
		else break;
	}
	cout << cnt << endl;
}
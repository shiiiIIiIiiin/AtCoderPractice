#include<iostream>
#include<vector>
#include<queue>
#include<climits>
using namespace std;
using ll = long long;

int main() {
	int N; cin >> N;
	vector<bool> f(N + 1,false);
	for (int i = 0; i < N; i++) {
		int a; cin >> a;
		if (f[a]) {
			cout << "No";
			return 0;
		}
		f[a] = true;
	}

	cout << "Yes";
}
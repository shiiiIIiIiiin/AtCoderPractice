#include<iostream>
#include<vector>
#include<stdlib.h>
using namespace std;

int main() {
	int N, K; cin >> N >> K;
	int ans = 0;

	for (int i = 100; i <= 1000; i++) {
		int a = i % 10, b = (i / 10) % 10, c = i / 100;

		if (a!=0&&a <= K && b == 0 && c!=0&&c <= N)ans += i;
	}
	cout << ans << endl;

}
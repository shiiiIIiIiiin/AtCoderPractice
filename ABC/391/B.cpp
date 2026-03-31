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
	int N, M; cin >> N >> M;
	vector<string> S(N), T(M);
	for (int i = 0; i < N; i++)cin >> S[i];
	for (int i = 0; i < M; i++)cin >> T[i];

	for (int a = 0; a + M <= N; a++) {
		for (int b = 0; b + M <= N; b++) {
			bool can = true;

			for (int h = a; h - a < M; h++)for (int w = b; w - b < M; w++) {
				if (S[h][w] != T[h - a][w - b])can=false;
			}

			if (can) {
				cout << a + 1 << " " << b + 1;
				return 0;
			}
		}
	}
}
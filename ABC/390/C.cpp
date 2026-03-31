#include<iostream>
#include<vector>
#include<queue>
#include<climits>
#include<algorithm>
#include<map>
#include<set>
using namespace std;
using ll = long long;

int H, W;

int main() {
	cin >> H >> W;
	vector<string> S(H);
	for (int i = 0; i < H; i++)cin >> S[i];

	//一番左上と一番右下を見つける
	int ml = INT_MAX, MR = -1, mu = INT_MAX, MD = -1;

	for (int i = 0; i < H; i++)for (int j = 0; j < W; j++) {
		if (S[i][j] != '#')continue;

		ml = min(ml, j);
		MR = max(MR, j);
		mu = min(mu, i);
		MD = max(MD, i);
	}

	for (int i = mu; i <= MD; i++)for (int j = ml; j <= MR; j++) {
		if (S[i][j] == '.') {
			cout << "No";
			return 0;
		}
	}

	cout << "Yes";
}
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
	
    vector<string> s = {
        "###.?????",
        "###.?????",
        "###.?????",
        "....?????",
        "?????????",
        "?????....",
        "?????.###",
        "?????.###",
        "?????.###",
    };
    vector<string> S(N);
    for (int i = 0; i < N; i++)cin >> S[i];

    for (int i = 0; i <= N - 9; i++)for (int j = 0; j <= M - 9; j++) {
        bool check = true;

        for (int h = 0; h < 9; h++)for (int w = 0; w < 9; w++)if (s[h][w] != S[i + h][j + w]&&s[h][w]!='?')check = false;
   
        if (check)cout << i + 1 << " " << j + 1 << endl;
    }

}
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    string S;
    cin >> S;

    vector<int> ans(N, 0);
    vector<int> heights(N, 1);

    // 前からAを満たすように設定
    for (int i = 0; i < S.size(); i++) {
        if (S[i] == 'A') {
            heights[i + 1] = heights[i] + 1;
        }
    }

    // 後ろからBを満たすように調整
    for (int i = S.size() - 1; i >= 0; i--) {
        if (S[i] == 'B' && heights[i] <= heights[i + 1]) {
            heights[i] = heights[i + 1] + 1;
        }
    }

    // 合計を計算
    int sum = accumulate(heights.begin(), heights.end(), 0);
    cout << sum << endl;

    return 0;
}
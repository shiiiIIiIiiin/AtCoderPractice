#include<bits/stdc++.h>
using namespace std;

long long solve(int &N, vector<int> &X, vector<long long> &P, int l, int r) {
    // l 以上の最初の要素の位置を取得
    int L = lower_bound(X.begin(), X.end(), l) - X.begin();
    // r より大きい最初の要素の位置を取得
    int R = upper_bound(X.begin(), X.end(), r) - X.begin();

    // LがN以上、またはRが0の場合には範囲外なので、答えは0
    if (L >= N || R == 0) {
        return 0;
    }

    // R-1が範囲外にならないように調整
    if (R > N) R = N;

    // L-1が負の値にならないように調整
    return P[R-1] - (L > 0 ? P[L-1] : 0);
}

int main() {
    int N;
    cin >> N;
    vector<int> X(N);  // XはN要素の配列
    for (int i = 0; i < N; i++) cin >> X[i];
    
    vector<long long> P(N);  // PもN要素の累積和
    for (int i = 0; i < N; i++) cin >> P[i];

    // 累積和を計算
    for (int i = 1; i < N; i++) P[i] += P[i-1];

    int Q;
    cin >> Q;

    for (int i = 0; i < Q; i++) {
        int l, r;
        cin >> l >> r;
        cout << solve(N, X, P, l, r) << endl;
    }

    return 0;
}
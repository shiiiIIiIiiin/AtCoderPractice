#include <bits/stdc++.h>
using namespace std;

int main() {
    long long N;
    cin >> N;
    vector<long long> A(N), B(N);
    for (long long i = 0; i < N; i++) cin >> A[i] >> B[i];

    // 成功率と番号のペアを作成
    vector<pair<long long, long long>> P(N); // (番号, インデックス)
    for (long long i = 0; i < N; i++) {
        P[i] = {i + 1, i};
    }

    // 比較関数で整数演算を使用
    stable_sort(P.begin(), P.end(), [&](const pair<long long, long long>& a, const pair<long long, long long>& b) {
        long long A1 = A[a.second], B1 = B[a.second];
        long long A2 = A[b.second], B2 = B[b.second];
        if (A1 * (A2 + B2) != A2 * (A1 + B1)) {
            return A1 * (A2 + B2) > A2 * (A1 + B1); // 成功率を比較
        }
        return a.first < b.first; // 番号を昇順で比較
    });

    // 結果を出力
    for (long long i = 0; i < N; i++) {
        cout << P[i].first << " ";
    }

    return 0;
}
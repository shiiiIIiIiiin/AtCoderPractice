#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    set<pair<int, int>> s;  // 各要素の値とそのインデックスを保持するセット
    vector<int> B(N, -1);   // 出力用の配列

    for (int i = 0; i < N; i++) {
        cin >> A[i];
        auto it = s.lower_bound(make_pair(A[i], -1));

        // 値が存在する場合、それをBに記録し削除
        if (it != s.end() && it->first == A[i]) {
            B[i] = it->second;  // 見つかったペアのインデックスを格納
            s.erase(it);
        }

        // 新しいペアをセットに挿入
        s.insert(make_pair(A[i], i + 1));
    }

    // 結果の出力
    for (int i = 0; i < N; i++) {
        cout << B[i] << " ";
    }
    cout << endl;

    return 0;
}
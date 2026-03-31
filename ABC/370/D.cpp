#include <bits/stdc++.h>
using namespace std;

int main() {
    int H, W, Q;
    cin >> H >> W >> Q;

    // セルが空白でないかを管理するためのデータ構造
    vector<set<int>> r(H), c(W);

    // 初期状態で全てのセルが空白でないとする
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            r[i].insert(j);
            c[j].insert(i);
        }
    }

    // セルを空白にするためのヘルパー関数
    auto erase = [&](int i, int j) {
        r[i].erase(j);
        c[j].erase(i);
    };

    while (Q--) {
        int R, C;
        cin >> R >> C;
        --R, --C;

        if (r[R].count(C)) {
            // セルが空白でない場合、空白にする
            erase(R, C);
        } else {
            // セルがすでに空白の場合、周囲のセルを更新
            // 上
            {
                auto it = c[C].lower_bound(R);
                if (it != c[C].begin()) {
                    erase(*prev(it), C);
                }
            }
            // 下
            {
                auto it = c[C].lower_bound(R);
                if (it != c[C].end()) {
                    erase(*it, C);
                }
            }
            // 左
            {
                auto it = r[R].lower_bound(C);
                if (it != r[R].begin()) {
                    erase(R, *prev(it));
                }
            }
            // 右
            {
                auto it = r[R].lower_bound(C);
                if (it != r[R].end()) {
                    erase(R, *it);
                }
            }
        }
    }

    // 最終的な空白でないセルの数をカウント
    int ans = 0;
    for (const auto& row : r) {
        ans += row.size();
    }

    cout << ans << "\n";

    return 0;
}
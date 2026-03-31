#include <bits/stdc++.h>
using namespace std;

int main() {
    string S;
    cin >> S;
    vector<int> cnt(10, 0);

    for (char c : S) cnt[c - '0']++;

    // 長さが3未満の場合は直接数字を生成して判定
    if (S.size() < 3) {
        sort(S.begin(), S.end());
        do {
            int num = stoi(S);
            if (num % 8 == 0) {
                cout << "Yes" << endl;
                return 0;
            }
        } while (next_permutation(S.begin(), S.end()));
        cout << "No" << endl;
        return 0;
    }

    // 3桁以上の場合、すべての8の倍数を確認
    for (int i = 8; i < 1000; i += 8) {
        vector<int> c(10, 0);
        int x = i;
        for (int j = 0; j < 3; j++) {
            c[x % 10]++;
            x /= 10;
        }

        bool valid = true;
        for (int j = 0; j < 10; j++) {
            if (cnt[j] < c[j]) {
                valid = false;
                break;
            }
        }

        if (valid) {
            cout << "Yes" << endl;
            return 0;
        }
    }

    // 特別ケース（1000の倍数を作れるかチェック）
    if (cnt[0] >= 3) {
        cout << "Yes" << endl;
        return 0;
    }

    cout << "No" << endl;
    return 0;
}
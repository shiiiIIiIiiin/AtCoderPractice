#include <bits/stdc++.h>
using namespace std;

// 素因数の個数を計算する関数
int countPrimeFactors(int num) {
    int count = 0;
    // 2で割り切れる限り割り続ける
    while (num % 2 == 0) {
        count++;
        num /= 2;
    }
    // 奇数の素因数で割り続ける
    for (int i = 3; i * i <= num; i += 2) {
        while (num % i == 0) {
            count++;
            num /= i;
        }
    }
    // num が素数で 2 より大きい場合
    if (num > 2) {
        count++;
    }
    return count;
}

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];

    // 素因数の個数をGrundy数としてカウント
    int nim_sum = 0;
    for (int i = 0; i < N; ++i) {
        int grundy_number = countPrimeFactors(A[i]);
        nim_sum ^= grundy_number;  // ニム和の計算
    }

    // 勝者の判定
    if (nim_sum == 0) {
        cout << "Bruno" << endl;  // 後手が勝つ
    } else {
        cout << "Anna" << endl;   // 先手が勝つ
    }

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

// 素数の篩（エラトステネスの篩）を使って素数リストを作成
void makePrime(vector<bool> &p) {
    for (long long i = 2; i * i < 1000000; i++) {
        if (p[i]) {
            for (int j = i * i; j < 1000000; j += i) p[j] = false;
        }
    }
}

int main() {
    long long N;
    cin >> N;

    // 素数リストの作成
    vector<bool> p(1000000, true);
    p[0] = p[1] = false;
    makePrime(p);

    // 素数を収集
    vector<long long> primes;
    for (long long i = 2; i < 1000000; i++) {
        if (p[i]) primes.push_back(i);
    }

    long long ans = 0;
    // i と j の組み合わせを探索
    for (long long i = 0; i < primes.size()-1; i++) {
        for (long long j = i + 1; j < primes.size(); j++) {
            // オーバーフロー防止のため型を拡張して計算
            if (primes[i]*primes[j]*primes[j] > (double)N/(double)primes[j]) break;
            ans++;
        }
    }

    // 結果の出力
    cout << ans << endl;
    return 0;
}
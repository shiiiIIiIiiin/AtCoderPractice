//#define _GLIBCXX_DEBUG

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <map>
#include <set>
#include <iterator>
#include <unordered_map>
#include <stack>
#include <string>
#include <cmath>
#include <iomanip>
#include <deque>
#include <unordered_set>
#include <locale>
#include <random>

using namespace std;
using ll = long long;

const ll MOD = 998244353;
const ll MOD2 = 1'000'000'007;

long long modinv(long long a, long long m) {
    long long b = m, u = 1, v = 0;
    while (b) {
        long long t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    u %= m; if (u < 0) u += m;
    return u;
}

long long modpow(long long a, long long n, long long mod) {
    long long res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}


int dx[] = { 1, 0, -1, 0 }, dy[] = { 0, 1, 0, -1 };

const ll INF = LLONG_MAX / 2;

//cin.tie(nullptr);
//ios::sync_with_stdio(false);

int N;

int check(int x, int y, vector<string>& S) {
    int res = 10;

    int cnt = 10;

    if (x + 5 < N) {
        cnt = 0;
        for (int i = 0; i < 6; i++)if (S[x + i][y] == '.')cnt++;
    }

    res = min(res, cnt);

    cnt = 10;

    if (y + 5 < N) {
        cnt = 0;
        for (int i = 0; i < 6; i++)if (S[x][y + i] == '.')cnt++;
    }
    
    res = min(res, cnt);
    cnt = 10;

    if (x + 5 < N && y + 5 < N) {
        cnt = 0;
        for (int i = 0; i < 6; i++)if (S[x + i][y + i] == '.')cnt++;
    }

    res = min(res, cnt);
    cnt = 10;

    if (x + 5 < N && y - 5 >= 0) {
        cnt = 0;
        for (int i = 0; i < 6; i++)if (S[x + i][y - i] == '.')cnt++;
    }
    res = min(res, cnt);


    return res;
}

int main() {
    cin >> N;
    vector<string> S(N);
    for (int i = 0; i < N; i++)cin >> S[i];

    //ありうる全てのラインについて、後何個必要か調べる

    for (int i = 0; i < N; i++)for (int j = 0; j < N; j++) {
        //(i,j)を中心に下に6、右に6、右下に6、右上に6伸ばしてみる
        if (check(i, j, S) <= 2) {
            cout << "Yes";
            return 0;
        }
    }

    cout << "No";
}
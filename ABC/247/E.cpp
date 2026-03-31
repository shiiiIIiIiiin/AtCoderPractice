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



/*

区間 [k,l] が区間 [i,j] を含んでいる、すなわち i,j,k,l が 1≤k≤i≤j≤l≤∣B∣ の関係にあるとき、区間
[i,j] が条件を満たすならば [k,l] が条件を満たす。

このような場合は次のようなアルゴリズムによって、条件を満たす区間を数え上げることができます。

はじめ、
・L=R=1 とする。
・L が N 以下の間、次の操作を行う。
　　区間[L,R] が条件を満たさない間、R に 1 を足す。
    条件を満たす[L,R] が見つかれば、区間[L,x](R≤x≤B) はすべて条件を満たすことになるので、その分を答えに加算する。
    L に 1 を加える。



*/

int main() {
    int N, X, Y; cin >> N >> X >> Y;
    vector<int> A(N);
    for (int i = 0; i < N; i++)cin >> A[i];

    vector<vector<int>> B;

    for (int i = 0; i < N; i++) {
        vector<int> memo;
        while (i < N && Y <= A[i] && A[i] <= X) {
            memo.push_back(A[i]);
            i++;
        }

        B.push_back(memo);
    }

    ll ans = 0;

    for (auto v : B) {
        int n = v.size(), count_x = 0, count_y = 0, r = 0;

        for (int l = 0; l < n; l++) {
            while (r < n && (count_x == 0 || count_y == 0)) {
                if (v[r] == X)count_x++;
                if (v[r] == Y)count_y++;

                r++;
            }

            if (count_x > 0 && count_y > 0)ans += n - r + 1;

            if (l == r)r++;
            else {
                if (v[l] == X)count_x--;
                if (v[l] == Y)count_y--;
            }
        }

    }

    cout << ans << endl;
}
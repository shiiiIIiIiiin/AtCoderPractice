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

int main() {
    int N, S; cin >> N >> S;
    vector<vector<char>> dp(N + 1, vector<char>(S + 1, 'C'));

    /*
    
    dp[n][s]:=n日目まででs円使う買い方があるか

    */

    dp[0][0] = 'D';

    vector<int> A(N + 1), B(N + 1);
    for (int i = 1; i <= N; i++)cin >> A[i] >> B[i];

    for (int n = 1; n <= N; n++) {
        for (int s = 0; s <= S; s++) {
            //dp[n][s] = dp[n - 1][s - A[n]] || dp[n - 1][s - B[n]];
            if (s - A[n] >= 0 && dp[n - 1][s - A[n]] != 'C')dp[n][s] = 'A';
            else if (s - B[n] >= 0 && dp[n - 1][s - B[n]] != 'C')dp[n][s] = 'B';
        }
    }


    if (dp[N][S] == 'C') {
        cout << "Impossible" << endl;
        return 0;
    }

    string ans = "";

    while (S != 0 || N != 0) {
        ans += dp[N][S];
        if (dp[N][S] == 'A')S -= A[N];
        else S -= B[N];
        N--;
    }
    
    if (ans.back() == 'D')ans.pop_back();

    reverse(ans.begin(), ans.end());

    cout << ans << endl;
}
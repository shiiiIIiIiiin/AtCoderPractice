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


class UnionFind {
public:
    vector<ll> siz, par;
    UnionFind(ll n) {
        siz.assign(n, 1);
        par.assign(n, -1);
    }
    ll root(ll x) {
        return par[x] == -1 ? x : par[x] = root(par[x]);
    }
    void unite(ll x, ll y) {
        ll rx = root(x), ry = root(y);
        if (rx == ry) return;
        if (siz[rx] < siz[ry]) {
            par[rx] = ry;
            siz[ry] += siz[rx];
        }
        else {
            par[ry] = rx;
            siz[rx] += siz[ry];
        }
    }
    bool same(ll x, ll y) {
        return root(x) == root(y);
    }
};

int dx[] = { 1, 0, -1, 0 }, dy[] = { 0, 1, 0, -1 };

const ll INF = LLONG_MAX / 2;

//cin.tie(nullptr);
//ios::sync_with_stdio(false);

int main() {
    string S; cin >> S;
    //dpでできる？
    /*
    
    dp[i][j]=i文字目まで考えて、関数の値がjであるようなやり方の総数
    求める答えはdp[N][0]である

    vector<vector<ll>> dp(N,vector<ll>(N))

    if(S[i]=='?'){
       dp[i][j]=dp[i-1][j-1]+dp[i-1][j+1]
    }
    else if(S[i]=='('){
       dp[i][j]=dp[i-1][j-1]
    }else if(S[i]==')'){
       dp[i][j]=dp[i-1][j+1]
    }

    */

    int N = S.size();
    vector<vector<ll>> dp(N + 1, vector<ll>(N + 1, 0));

    dp[0][0] = 1;

    for (int i = 1; i <= N; i++) {
        if (S[i - 1] == '?') {
            for (int j = 0; j <= N; j++) {
                if (j - 1 >= 0)dp[i][j] += dp[i - 1][j - 1];
                if (j + 1 <= N)dp[i][j] += dp[i - 1][j + 1];

                dp[i][j] %= MOD;
                //dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j + 1];
            }
        }
        else if(S[i-1]=='(') {
            for (int j = 0; j <= N; j++) {
                if (j - 1 >= 0)dp[i][j] = dp[i - 1][j - 1];
                dp[i][j] %= MOD;
            }
        }
        else {
            for (int j = 0; j <= N; j++) {
                if (j + 1 <= N)dp[i][j] = dp[i - 1][j + 1];
                dp[i][j] %= MOD;
            }
        }
    }


    cout << dp[N][0] << endl;
}
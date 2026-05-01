//#define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
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

ll dx[] = { 1, 0, -1, 0 }, dy[] = { 0, 1, 0, -1 };
const ll INF = LLONG_MAX / 2;

int dfs(vector<int>& memo, vector<int>& down, int pos) {
    if (down[pos] == -1) {
        memo[pos] = pos;
        return pos;
    }

    if (memo[pos] >= 0)return memo[pos];

    return memo[pos] = dfs(memo, down, down[pos]);
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int N, Q; cin >> N >> Q;
    //それぞれのカードを連結リスト方式で持っておけばいい

    vector<int> down(N + 1, -1);//下のカードをメモする

    for (; Q--;) {
        int c, p; cin >> c >> p;
        down[c] = p;
    }

    vector<int> memo(N + 1, -100);//memo[i]:=カードiがどの山にいるか, 一番下のカードは一回も動いてないことが保証される

    for (int i = 1; i <= N; i++)dfs(memo, down, i);

    vector<int> ans(N + 1, 0);
    for (int i = 1; i <= N; i++)ans[memo[i]]++;

    for (int i = 1; i <= N; i++)cout << ans[i] << " ";
}
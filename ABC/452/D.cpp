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

bool check(string& S, string& T, vector<vector<ll>>& idx, ll l, ll r) {
    int cnt = l;

    for (int i = 0; i < T.size(); i++) {
        cnt = idx[cnt][T[i] - 'a'];
        if (cnt >= r)return false;
        cnt++;
    }

    return true;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    string S, T; cin >> S >> T;

    //尺取り法でいく、Tが短い

    int N = S.size(), M = T.size();

    ll r = 0, ans = 0;

    /*次にどこで文字が出てくるかの表を用意しておけば、checkを高速に行うことができる
      典型90でライブラリ化してもいいって言ってた（？）やつ
    */

    vector<vector<ll>> idx(N + 1, vector<ll>(26, N));
    //idx[n]['x'-'a']:=文字xがn番目以降でどこで一番最初に出てくるか

    for (int n = N - 1; n >= 0; n--) {
        for (int i = 0; i < 26; i++)idx[n][i] = idx[n + 1][i];
        idx[n][S[n] - 'a'] = n;
    }

    for (int l = 0; l < N; l++) {
        while (r < N && !check(S, T, idx, l, r + 1)) {
            r++;
        }

        ans += r - l;
        
        if (r == l)r++;
        else {

        }
    }

    cout << ans << endl;
}
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

//cin.tie(nullptr);
//ios::sync_with_stdio(false);

vector<string> po2;

void dfs(string s, vector<ll>& ans) {
    for (int i = 0; i < po2.size(); i++) {
        string t = s + po2[i];
        if (t.size() >= 10)break;
        ans.push_back(stoll(t));
        dfs(t, ans);
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    vector<ll> ans;

    string s = "";
    ll cnt = 1;

    while (cnt <= 1e9) {
        po2.push_back(to_string(cnt));
        cnt *= 2;
    }

    dfs(s, ans);
    sort(ans.begin(), ans.end());

    ans.erase(unique(ans.begin(), ans.end()), ans.end());

    cout << ans[N - 1] << endl;
}
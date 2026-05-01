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


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int Q; cin >> Q;
    string s = "";
    vector<int> cnt_history = { 0 }, min_history = { 0 };

    for (; Q--;) {
        int t; cin >> t;

        if (t == 1) {
            char c; cin >> c;

            int cnt = cnt_history.back(), m = min_history.back();

            cnt += (c == '(' ? 1 : -1);
            m = min(m, cnt);

            cnt_history.push_back(cnt);
            min_history.push_back(m);
        }
        else {
            cnt_history.pop_back();
            min_history.pop_back();
        }

        if (cnt_history.back() == 0 && min_history.back() >= 0)cout << "Yes" << endl;
        else cout << "No" << endl;

    }
}
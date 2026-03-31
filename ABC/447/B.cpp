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
    string S; cin >> S;
    vector<int> cnt(26, 0);
    int N = S.size();

    for (int i = 0; i < N; i++)cnt[S[i] - 'a']++;

    int M = -1;
    set<char> ids;
    for (int i = 0; i < 26; i++) {
        if (M < cnt[i]) {
            M = cnt[i];
            ids.clear();
            ids.insert(i + 'a');
        }
        else if (M == cnt[i]) {
            ids.insert(i + 'a');
        }
    }

    for (int i = 0; i < N; i++)if (!ids.count(S[i]))cout << S[i];
}
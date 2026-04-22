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

void check(string& s) {
    if (s.size() < 4)return;

    int n = s.size();

    if (s[n - 4] == '(' && s[n - 3] == 'x' && s[n - 2] == 'x' && s[n - 1] == ')') {
        for (int i = 0; i < 4; i++)s.pop_back();
        s += "xx";
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int T; cin >> T;

    for (; T--;) {
        string A, B; cin >> A >> B;

        //xの数が違ったら無理
        int c1 = 0, c2 = 0;
        for (int i = 0; i < A.size(); i++)c1 += A[i] == 'x';
        for (int i = 0; i < B.size(); i++)c2 += B[i] == 'x';

        if (c1 != c2) {
            cout << "No" << endl;
            continue;
        }

        //可能な限り()を取り除いていって一致すればいい？

        string st1, st2;

        for (auto c : A) {
            st1 += c;
            check(st1);
        }

        for (auto c : B) {
            st2 += c;
            check(st2);
        }

        cout << (st1 == st2 ? "Yes" : "No") << endl;
    }
}
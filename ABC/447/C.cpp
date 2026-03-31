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

ll dx[] = { 1, 0, -1, 0 }, dy[] = { 0, 1, 0, -1 };
const ll INF = LLONG_MAX / 2;

pair<string, vector<int>> get_info(string str) {
    string s;
    vector<int> res;

    int N = str.size();

    for (int i = 0; i < N; i++) {
        int c = 0;
        while (i < N && str[i] == 'A') {
            c++;
            i++;
        }

        res.push_back(c);
        if (i < N)s += str[i];
    }

    return { s,res };
}

int main() {
    string S, T; cin >> S >> T;

    S = 'A' + S + 'A';
    T = 'A' + T + 'A';
    auto s = get_info(S), t = get_info(T);

    if (s.first != t.first) {
        cout << -1 << endl;
        return 0;
    }

    int ans = 0;

    vector<int> ss = s.second, tt = t.second;
    
    for (int i = 0; i < ss.size(); i++)ans += abs(ss[i] - tt[i]);

    cout << ans << endl;
}
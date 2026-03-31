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

vector<ll> X;
vector<ll> d;

ll get_val(int id) {
    if (d[id] > INF / 2)return 0;
    return d[id];
}

int main() {
    int N; cin >> N;
    X.resize(N + 3);
    for (int i = 1; i <= N; i++)cin >> X[i];
    X[N + 1] = -INF;
    X[N + 2] = INF;
    
    d.resize(N + 3, INF);

    d[N + 1] = 0;
    d[N + 2] = 0;

    set<pair<ll, int>> st;
    st.insert({ 0,0 });
    st.insert({ -INF,N + 1 });
    st.insert({ INF,N + 2 });

    ll ans = 0;

    for (int i = 1; i <= N; i++) {
        auto itr = st.lower_bound({ X[i],0 }), itl = prev(itr);
        int l = itl->second, r = itr->second;
        ans -= get_val(l) + get_val(r);
        d[l] = min(d[l], abs(X[l] - X[i]));
        d[r] = min(d[r], abs(X[r] - X[i]));
        d[i] = min(abs(X[r] - X[i]), abs(X[l] - X[i]));
        ans += get_val(l) + get_val(r) + get_val(i);

        st.insert({ X[i],i });

        cout << ans << endl;
    }
}
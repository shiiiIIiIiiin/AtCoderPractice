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
    int N; cin >> N;
    vector<int> A(N);

    for (int i = 0; i < N; i++)cin >> A[i];

    int ans = 0;

    for (int start = 0; start < 2; start++) {//偶数開始を奇数開始でループを回す
        int r, l;
        r = l = start;
        vector<int> cnt(N + 1);

        while (r + 1 < N) {
            if (A[r] != A[r + 1]) {//そもそもそろってないのでリセットする
                while (l != r) {
                    cnt[A[l]]--;
                    l += 2;
                }

                r += 2;
                l = r;
            }
            else {//尺取り法をする
                cnt[A[r]]++;

                while (cnt[A[r]] >= 2) {
                    cnt[A[l]]--;
                    l += 2;
                }

                r += 2;
                ans = max(ans, r - l);

            }
        }
    }

    cout << ans << endl;
}
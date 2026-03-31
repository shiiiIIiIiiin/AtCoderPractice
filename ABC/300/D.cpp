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

using namespace std;
using ll = long long;

const ll MOD = 998244353;
const ll MOD2 = 1'000'000'007;

class SegTree {
public:
    vector<ll> dat;
    ll siz = 1;

    SegTree(ll n) {
        while (siz < n) siz *= 2;
        dat.resize(2 * siz, -LLONG_MAX);
    }

    void update(int id, ll x) {
        id += siz;
        dat[id] = x;
        while (id != 0) {
            id /= 2;
            dat[id] = max(dat[2 * id], dat[2 * id + 1]);
        }
    }

    ll getval(int id) {
        return dat[id + siz];
    }

    ll getmax(ll L, ll R, ll a, ll b, ll u) {
        if (b <= L || R <= a) return -LLONG_MAX / 2;
        if (L <= a && b <= R) return dat[u];
        ll m = (a + b) / 2;
        return max(getmax(L, R, a, m, 2 * u),
            getmax(L, R, m, b, 2 * u + 1));
    }
};

class UnionFind {
public:
    vector<int> siz, par;
    UnionFind(int n) {
        siz.assign(n, 1);
        par.assign(n, -1);
    }
    int root(int x) {
        return par[x] == -1 ? x : par[x] = root(par[x]);
    }
    void unite(int x, int y) {
        int rx = root(x), ry = root(y);
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
    bool same(int x, int y) {
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

//ios::sync_with_stdio(false);
//cin.tie(nullptr);



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    ll N; cin >> N;
    //a^5<Nである　これは全探索できる
    //a^2*b^3<N である　これも全探索できる？
    //c^2=N/(a^2*b) であり、cが整数になるかは二分探索とか？

    //まず、10^6までの素数を全列挙することにする

    
    vector<bool> is_prime(1000010, true);

    is_prime[0] = is_prime[1] = false;

    for (ll i = 2; i < is_prime.size(); i++) {
        if (is_prime[i]) {
            for (ll j = i * 2; j < is_prime.size(); j += i)is_prime[j] = false;
        }
    }

    vector<ll> primes;
    for (ll i = 2; i < is_prime.size(); i++)if (is_prime[i])primes.push_back(i);

    ll n = primes.size();
    ll ans = 0;

    
    for (ll i = 0; i < n; i++) {
        ll a = primes[i];
        if (a * a * a * a * a > N)break;//全列挙終わり
        
        for (ll j = i + 1; j < n; j++) {
            ll b = primes[j];
            if (a * a * b * b * b >= N)break;
           
            
            for (ll k = j + 1; k < n; k++) {
                ll c = primes[k];

                if (a * a * b * c * c > N)break;

                ans++;
            }

        }
    }

    cout << ans << endl;
    
    
    
}
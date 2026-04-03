#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using ll = long long;

const ll MOD = 998244353;
const ll MOD2 = 1'000'000'007;

long long modinv(long long a, long long m)
{
    long long b = m, u = 1, v = 0;
    while (b)
    {
        long long t = a / b;
        a -= t * b;
        swap(a, b);
        u -= t * v;
        swap(u, v);
    }
    u %= m;
    if (u < 0)
        u += m;
    return u;
}

long long modpow(long long a, long long n, long long mod)
{
    long long res = 1;
    while (n > 0)
    {
        if (n & 1)
            res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

ll dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
const ll INF = LLONG_MAX / 2;

ll op(ll a, ll b)
{
    return max(a, b);
}
ll e()
{
    return 0;
}
ll mapping(ll f, ll s)
{
    return f == -1 ? s : f;
}
ll composition(ll f, ll g)
{
    return f == -1 ? g : f;
}
ll id()
{
    return -1;
}

int main()
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    ll W, N;
    cin >> W >> N;

    lazy_segtree<ll, op, e, ll, mapping, composition, id> lazy_segtree(W + 1);

    for (int i = 0; i < N; i++)
    {
        ll L, R;
        cin >> L >> R;
        ll mx = lazy_segtree.prod(L, R + 1);
        lazy_segtree.apply(L, R + 1, mx + 1);
        cout << mx + 1 << endl;
    }
}
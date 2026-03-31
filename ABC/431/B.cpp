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

    ll getmax_query(ll L, ll R, ll a, ll b, ll u) {
        if (b <= L || R <= a) return -LLONG_MAX / 2;
        if (L <= a && b <= R) return dat[u];
        ll m = (a + b) / 2;
        return max(getmax_query(L, R, a, m, 2 * u),
            getmax_query(L, R, m, b, 2 * u + 1));
    }

    ll getmax(ll L, ll R) {
        return getmax_query(L, R, 0, siz, 1);
    }
};

class LazySegTree {
public:
    int siz = 1;
    vector<ll> dat, lazy;

    LazySegTree(int n) {
        while (siz < n) siz *= 2;
        dat.assign(2 * siz, 0);  // 区間和なので単位元は0
        lazy.assign(2 * siz, 0); // 遅延の単位元（更新がない状態）も0
    }

    // 遅延情報を子ノードに伝播させる
    void push(int k, int l, int r) {
        if (lazy[k] == 0) return; // 遅延している更新がなければ何もしない

        // 自分のデータノードに遅延情報を反映
        dat[k] += lazy[k] * (r - l);

        // 子ノードが存在する場合、子ノードのlazyに情報を伝播させる
        if (r - l > 1) {
            lazy[2 * k] += lazy[k];
            lazy[2 * k + 1] += lazy[k];
        }

        // 自分の遅延情報は解消
        lazy[k] = 0;
    }

    // 区間 [a, b) に値 x を加算する
    // k: 現在のノード, [l, r): kが表す区間
    void update(int a, int b, ll x, int k, int l, int r) {
        push(k, l, r); // 遅延情報を先に評価する

        if (r <= a || b <= l) return; // 範囲外なら何もしない

        if (a <= l && r <= b) { // 範囲が完全に含まれる場合
            lazy[k] += x;       // 遅延配列に更新を記録
            push(k, l, r);      // すぐに自身のdatにも反映させておく
            return;
        }

        int m = (l + r) / 2;
        update(a, b, x, 2 * k, l, m);
        update(a, b, x, 2 * k + 1, m, r);

        // 子ノードの更新が完了したら、自身のdatを更新
        dat[k] = dat[2 * k] + dat[2 * k + 1];
    }
    // ユーザー向けの update 関数
    void update(int a, int b, ll x) {
        update(a, b, x, 1, 0, siz);
    }


    // 区間 [a, b) の合計値を取得する
    ll query(int a, int b, int k, int l, int r) {
        push(k, l, r); // 遅延情報を先に評価する

        if (r <= a || b <= l) return 0; // 範囲外なら単位元を返す

        if (a <= l && r <= b) return dat[k]; // 完全に含まれていればその値を返す

        int m = (l + r) / 2;
        ll res_l = query(a, b, 2 * k, l, m);
        ll res_r = query(a, b, 2 * k + 1, m, r);
        return res_l + res_r;
    }
    // ユーザー向けの query 関数
    ll query(int a, int b) {
        return query(a, b, 1, 0, siz);
    }
};

class LazySegTree_RUQ { // Range Update Query
public:
    int siz = 1;
    vector<ll> dat, lazy;
    const ll INF_DATA = LLONG_MIN; // データ配列の単位元 (maxなので非常に小さい値)
    const ll INF_LAZY = LLONG_MAX; // lazy配列の単位元 (更新予約がないことを示す特別な値)


    LazySegTree_RUQ(int n) {
        while (siz < n) siz *= 2;
        dat.assign(2 * siz, 0); // 初期値は0など任意の値でOK
        lazy.assign(2 * siz, INF_LAZY);
    }

    // 遅延情報を子ノードに伝播
    void push(int k) {
        if (lazy[k] == INF_LAZY) return; // 更新予約がなければ何もしない

        // 子ノードに更新予約を上書き
        lazy[2 * k] = lazy[k];
        lazy[2 * k + 1] = lazy[k];

        // 自身のデータノードにも反映
        dat[k] = lazy[k];

        // 自身の予約は解消
        lazy[k] = INF_LAZY;
    }

    // 区間 [a, b) の値を x に更新する
    // k: 現在のノード, [l, r): kが表す区間
    void update(int a, int b, ll x, int k, int l, int r) {
        if (r <= a || b <= l) { // 範囲外なら何もしない
            return;
        }
        if (a <= l && r <= b) { // 完全に含まれる場合
            lazy[k] = x; // 予約を入れる
        }
        else {
            push(k); // 分割して下に潜る前に、自分の予約を子に伝播させる
            int m = (l + r) / 2;
            update(a, b, x, 2 * k, l, m);
            update(a, b, x, 2 * k + 1, m, r);

            // 子ノードの更新後、親の値を更新する
            dat[k] = max((lazy[2 * k] == INF_LAZY ? dat[2 * k] : lazy[2 * k]),
                (lazy[2 * k + 1] == INF_LAZY ? dat[2 * k + 1] : lazy[2 * k + 1]));
        }
    }
    // ユーザー向けの update 関数
    void update(int a, int b, ll x) {
        update(a, b, x, 1, 0, siz);
    }

    // 区間 [a, b) の最大値を取得する
    ll query(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) return INF_DATA; // 範囲外なら単位元

        if (lazy[k] != INF_LAZY) { // そのノードに予約があれば、区間全体がその値になっている
            return lazy[k];
        }
        if (a <= l && r <= b) {
            return dat[k];
        }

        int m = (l + r) / 2;
        ll res_l = query(a, b, 2 * k, l, m);
        ll res_r = query(a, b, 2 * k + 1, m, r);
        return max(res_l, res_r);
    }
    // ユーザー向けの query 関数
    ll query(int a, int b) {
        return query(a, b, 1, 0, siz);
    }
};

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
    int X, N; cin >> X >> N;
    vector<int> W(N + 1);
    for (int i = 1; i <= N; i++)cin >> W[i];

    int Q; cin >> Q;
    vector<bool> v(N + 1);

    for (; Q--;) {
        int p; cin >> p;

        if (v[p])X -= W[p];
        else X += W[p];

        v[p] = !v[p];

        cout << X << endl;
    }
}
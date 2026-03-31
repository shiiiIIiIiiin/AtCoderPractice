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

int dx[] = { 1, 0, -1, 0 }, dy[] = { 0, 1, 0, -1 };

const ll INF = LLONG_MAX / 2;

//cin.tie(nullptr);
//ios::sync_with_stdio(false);

int main() {
    int Ha, Wa; cin >> Ha >> Wa;
    vector<string> A(Ha);
    for (int i = 0; i < Ha; i++)cin >> A[i];
    int Hb, Wb; cin >> Hb >> Wb;
    vector<string> B(Hb);
    for (int i = 0; i < Hb; i++)cin >> B[i];
    int Hx, Wx; cin >> Hx >> Wx;
    vector<string> X(Hx);
    for (int i = 0; i < Hx; i++)cin >> X[i];

    //シートAの左上20×20マスを全探索、シートBの左上20×20マスを全探索、それぞれについて、O(HxWx)で判定

    
    //C[10][10]を切り出すところに左上とする

    for (int a = 0; a < 20; a++)for (int b = 0; b < 20; b++)for (int c = 0; c < 20; c++)for (int d = 0; d < 20; d++) {
        vector<string> C(30);
        for (int i = 0; i < 30; i++)for (int j = 0; j < 30; j++)C[i] += '.';

        for (int k = 0; k < Ha; k++)for (int l = 0; l < Wa; l++) {
            int x = a + k, y = b + l;
            C[x][y] = A[k][l];
        }

        for (int k = 0; k < Hb; k++)for (int l = 0; l < Wb; l++) {
            int x = c + k, y = d + l;
            if (C[x][y] == '#')continue;
            C[x][y] = B[k][l];
        }

        bool check = true;

        for (int i = 0; i < 30; i++)for (int j = 0; j < 30; j++) {
            if (10 <= i && i < 10 + Hx && 10 <= j && j < 10 + Wx)continue;
            if (C[i][j] == '#')check = false;
        }

        for (int x = 10; x < 10 + Hx && check; x++)for (int y = 10; y < 10 + Wx && check; y++) {
            if (C[x][y] != X[x - 10][y - 10]) {
                check = false;
                break;
            }
        }
        

        if (check) {
            cout << "Yes" << endl;
            return 0;
        }


    }

    cout << "No" << endl;
}
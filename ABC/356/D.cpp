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


int main() {
    //各桁について考える
    ll N, M; cin >> N >> M;
    
    /*k桁目について、0以上N以下の数でk桁目が立っている数字の個数をc(k)とすると、
    * 求めたい値は
    * Σc(k)*([Mのk桁目の数、0か1])　　のMODとなる
    */

    vector<ll> C(60);

    for (int i = 0; i < 60; i++) {
        //C[i]を埋めたい
        //上の桁から桁dp的に埋めていく？
        //いや、普通に計算できる
        ll p2 = (1LL << i), k = N / (2 * p2), res = k * p2, l = N % (2 * p2);

        if (l >= p2)res += (l - p2 + 1);

        C[i] = res;
    }

    ll ans = 0;

    for (int i = 0; i < 60; i++) {
        ans += C[i] * ((M >> i) & 1);
        ans %= MOD;
    }

    cout << ans << endl;
}
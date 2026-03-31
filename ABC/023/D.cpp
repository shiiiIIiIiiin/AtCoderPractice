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

bool check(ll x, vector<pair<ll, ll>>& P) {
    //タイムリミットはやばい順に打っていく？

    vector<ll> limit;
    int N = P.size();

    //タイムリミットは、(x-H)/Sの整数部分

    for (int i = 0; i < N; i++) {
        if (x - P[i].first < 0)return false;
        limit.push_back((x - P[i].first) / P[i].second);
    }

    sort(limit.begin(), limit.end());

    for (int i = 0; i < N; i++) {
        if (limit[i] < i)return false;
    }

    return true;
}

int main() {
    int N; cin >> N;
    vector<pair<ll, ll>> P(N);
    for (int i = 0; i < N; i++)cin >> P[i].first >> P[i].second;

    //Q[x]:=得点xを獲得できるか？

    ll l = -1, r = INF, m;

    while (r - l > 1) {
        m = (r + l) / 2;
        if (check(m, P))r = m;
        else l = m;
    }

    cout << r << endl;
}
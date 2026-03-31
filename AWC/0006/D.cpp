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
    int N, M; cin >> N >> M;
    vector<pair<ll, ll>> P(M);
    for (int i = 0; i < M; i++)cin >> P[i].first >> P[i].second;
    sort(P.begin(), P.end(), [&](const auto& a1, const auto& a2) {
        if (a1.first == a2.first)return a1.second > a2.second;
        return a1.first < a2.first;
        });

    ll maxR = -1;
    vector<pair<ll, ll>> use;
    for (int i = 0; i < M; i++) {
        if (P[i].second <= maxR)continue;
        maxR = P[i].second;
        use.push_back(P[i]);
    }

    //ここまでで意味のないものが消えた

    int ans = 0;
    ll R = 0, id = 0;

    while (R < N) {
        ll nex = id;
        while (nex < use.size() && use[nex].first <= R + 1)nex++;

        if (nex == id) {
            cout << -1 << endl;
            return 0;
        }

        ans++;
        R = use[nex - 1].second;
        id = nex;
    }

    cout << ans << endl;
}
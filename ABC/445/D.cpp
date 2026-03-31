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
#include<assert.h>

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

const ll INF = LLONG_MAX / 3;

//cin.tie(nullptr);
//ios::sync_with_stdio(false);


int main() {
    int H, W, N; cin >> H >> W >> N;
    vector<pair<ll, int>> P_h(N), P_w(N), P(N);
    for (int i = 0; i < N; i++) {
        cin >> P_h[i].first >> P_w[i].first;
        P[i].first = P_h[i].first;
        P[i].second = P_w[i].first;
        P_w[i].second = i;
        P_h[i].second = i;
    }

    sort(P_h.rbegin(), P_h.rend());
    sort(P_w.rbegin(), P_w.rend());
    P_h.push_back({ INF,-1 });
    P_w.push_back({ INF,-1 });

    vector<bool> used(N + 1);

    int idh = 0, idw = 0;
    vector<pair<int, int>> ans(N);

    while (idh < N || idw < N) {
        auto [h1, id1] = P_h[idh];
        auto [w2, id2] = P_w[idw];
        
        if (h1 == H) {
            if (used[id1]) {
                idh++;
                continue;
            }
            else {
                used[id1] = true;
                ll h = h1, w = P[id1].second;
                ans[id1] = { 1,W - w + 1 };
                W -= w;
                idh++;
            }
        }
        else if (w2 == W) {
            if (used[id2]) {
                idw++;
                continue;
            }
            else {
                used[id2] = true;
                ll h = P[id2].first, w = w2;
                ans[id2] = { H - h + 1,1 };
                H -= h;
                idw++;
            }
        }
        else {
            idh = min(N, idh + 1);
            idw = min(N, idw + 1);
        }
    }

    for (int i = 0; i < N; i++)cout << ans[i].first << " " << ans[i].second << endl;

}
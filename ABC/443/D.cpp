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
    int T; cin >> T;

    for (; T--;) {
        int N; cin >> N;
        vector<ll> R(N);
        using pli = pair<ll, int>;
        priority_queue<pli, vector<pli>, greater<pli>> pq;
        ll ans = 0;

        for (int i = 0; i < N; i++) {
            cin >> R[i];
            pq.push({ R[i],i });
        }

        vector<bool> visited(N);

        while (!pq.empty()) {
            auto [r, id] = pq.top(); pq.pop();
            
            if (visited[id])continue;
            visited[id] = true;

            //この両隣の駒を一個下まで持ってくる
            if (id != 0 && !visited[id - 1]) {
                ll pre = R[id - 1];
                R[id - 1] = min(R[id - 1], r + 1);
                ans += pre - R[id - 1];
                pq.push({ R[id - 1],id - 1 });
            }
            if (id + 1 < N && !visited[id + 1]) {
                ll pre = R[id + 1];
                R[id + 1] = min(R[id + 1], r + 1);
                ans += pre - R[id + 1];
                pq.push({ R[id + 1],id + 1 });
            }


        }

        cout << ans << endl;
    }
}
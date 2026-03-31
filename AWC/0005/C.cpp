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
    ll N, K; cin >> N >> K;
    vector<ll> A(N);
    for (int i = 0; i < N; i++)cin >> A[i];
    priority_queue<pair<ll, int>> pq;

    for (int i = 0; i < N; i++)pq.push({ A[i],i });
    vector<bool> used(N + 1, false);

    ll ans = 0;

    while (!pq.empty()) {
        auto [v, id] = pq.top(); pq.pop();
        if (used[id])continue;
        used[id] = true;

        //隣り合う花壇との差がK以下か調べる

        if (id != 0) {
            if (A[id] - A[id - 1] > K) {
                pq.push({ A[id] - K,id - 1 });
                ans += A[id] - K - A[id - 1];
                A[id - 1] = A[id] - K;
                //cout << id << " : " << A[id] - K - A[id - 1] << endl;
            }
        }

        if (id != N - 1) {
            if (A[id] - A[id + 1] > K) {
                pq.push({ A[id] - K,id + 1 });
                ans += A[id] - K - A[id + 1];
                A[id + 1] = A[id] - K;
                //cout << id << " : " << A[id] - K - A[id + 1] << endl;
            }
        }
    }

    cout << ans << endl;

}
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

int N;

void dfs(vector<ll>& cnt, vector<vector<int>>& G, int pos, int pre, ll& ans) {
    
    for (int i = 0; i < G[pos].size(); i++) {
        int nex = G[pos][i];
        if (nex == pre)continue;
        dfs(cnt, G, nex, pos, ans);
        cnt[pos] += cnt[nex];
        ans += (N - cnt[nex]) * cnt[nex];
    }

    cnt[pos]++;

}


int main() {
    cin >> N;
    vector<vector<int>> G(N + 1);
    for (int i = 0; i < N - 1; i++) {
        int a, b; cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    ll ans = 0;

    vector<ll> cnt(N + 1, 0);

    dfs(cnt, G, 1, -1, ans);

    cout << ans << endl;
}
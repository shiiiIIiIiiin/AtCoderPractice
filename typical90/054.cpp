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
    //グラフの辺の数をできる限り減らして最短経路問題にしたい
    //一度調べた論文は２度調べないことにする

    int N, M; cin >> N >> M;

    vector<vector<int>> G(N + 1);
    vector<vector<int>> paper(M);
    
    for (int i = 0; i < M; i++) {
        int k; cin >> k;
        for (int j = 0; j < k; j++) {
            int r; cin >> r;
            G[r].push_back(i);//人rが論文iを書いた
            paper[i].push_back(r);
        }
    }

    vector<bool> used_paper(M, false);
    vector<int> ans(N + 1, -1);

    queue<int> q;
    q.push(1);
    ans[1] = 0;

    while (!q.empty()) {
        int pos = q.front(); q.pop();

        for (int i = 0; i < G[pos].size(); i++) {
            int nex = G[pos][i];
            if (used_paper[nex])continue;

            used_paper[nex] = true;

            for (auto r : paper[nex])if (ans[r] == -1) {
                q.push(r);
                ans[r] = ans[pos] + 1;
            }
        }
    }

    for (int i = 1; i <= N; i++)cout << ans[i] << endl;
}
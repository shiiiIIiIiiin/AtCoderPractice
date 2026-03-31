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

int Dx[] = { 1, 0, -1, 0 }, Dy[] = { 0, 1, 0, -1 };

const ll INF = LLONG_MAX / 2;

//cin.tie(nullptr);
//ios::sync_with_stdio(false);

int N, M;
set<pair<int, int>> can_reach;

void dfs(vector<string>& S, vector<vector<bool>>& visited, int dx, int dy, int px, int py) {
    can_reach.insert({ px,py });

    while (px + dx >= 0 && px + dx < N && py + dy >= 0 && py + dy < M && S[px + dx][py + dy] == '.') {
        can_reach.insert({ px + dx,py + dy });
        px += dx;
        py += dy;
    }

    if (visited[px][py])return;
    visited[px][py] = true;

    for (int d = 0; d < 4; d++) {
        int ddx = Dx[d], ddy = Dy[d];
        if (ddx == dx && ddy == dy)continue;

        int nx = px + ddx, ny = py + ddy;

        if (S[nx][ny] == '.')dfs(S, visited, ddx, ddy, px, py);
    }

    return;
}

int main() {
    cin >> N >> M;
    vector<string> S(N);
    for (int i = 0; i < N; i++)cin >> S[i];

    int px = 1, py = 1;

    vector<vector<bool>> visited(N, vector<bool>(M));//ここ始点で滑り始められるか？
    visited[px][py] = true;
    can_reach.insert({ px,py });

    
    if (S[px + 1][py] == '.')dfs(S, visited, 1, 0, px, py);
    if (S[px][py + 1] == '.')dfs(S, visited, 0, 1, px, py);

    cout << can_reach.size() << endl;
}
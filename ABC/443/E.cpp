//#define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
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

ll dx[] = { 1,1,1 }, dy[] = { -1,0,1 };
const ll INF = LLONG_MAX / 2;

int N, C;
int next_wall_row[3005][3005];
int memo[3005][3005];

vector<string> S;

/*
bool check_visit(vector<vector<bool>>& can_visit, int x, int y, vector<string>& S, vector<vector<bool>>& cnt, vector<vector<bool>>& visited) {
    if (visited[x][y])return can_visit[x][y];
    visited[x][y] = true;

    if (x == N - 1) {
        if (y == C - 1)return true;
        return false;
    }


    if (S[x][y] == '.') {
        for (int d = 0; d < 3; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || N <= nx || ny < 0 || N <= ny)continue;
            if (check_visit(can_visit, nx, ny, S, cnt, visited)) {
                return can_visit[x][y] = true;
            }
        }

        return false;
    }
    else {
        int nx = x + 1, ny = y;
        if (S[nx][ny] == '#') {
            if (check_visit(can_visit, nx, ny, S, cnt, visited)) {
                can_visit[x][y] = true;
            }
        }
        else {
            for (int d = 0; d < 3; d++) {
                int nnx = x + dx[d], nny = y + dy[d];
                if (nnx < 0 || N <= nnx || nny < 0 || N <= nny)continue;
                if (check_visit(can_visit, nnx, nny, S, cnt, visited)) {
                    return can_visit[x][y] = true;
                }
            }
        }

        return can_visit[x][y];
    }
}
*/

bool can(int x, int y) {
    if (y < 0 || N <= y)return false;
    if (memo[x][y] != -1)return memo[x][y];

    if (x == N - 1)return memo[x][y] = (y == C);

    int next_w = next_wall_row[x][y];

    if (S[x][y] == '#' && next_w != -1)return memo[x][y] = can(next_w, y);
    else return memo[x][y] = can(x + 1, y - 1) || can(x + 1, y) || can(x + 1, y + 1);
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int T; cin >> T;

    for (; T--;) {
        cin >> N >> C; C--;
        S.resize(N);

        for (int i = 0; i < N; i++)for (int j = 0; j < N; j++)memo[i][j] = -1;
        for (int i = 0; i < N; i++)cin >> S[i];

        for (int j = 0; j < N; j++) {
            int last_w = -1;
            for (int i = N - 1; i >= 0; i--) {
                next_wall_row[i][j] = last_w;
                if (S[i][j] == '#')last_w = i;
            }
        }

        for (int i = 0; i < N; i++)cout << (can(0, i) ? '1' : '0');
        cout << endl;
    }

}
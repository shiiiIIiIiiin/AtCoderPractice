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

ll dx[] = { 1, 0, -1, 0 }, dy[] = { 0, 1, 0, -1 };
const ll INF = LLONG_MAX / 2;

class state {
public:
    int x, y, d;
};

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int H, W; cin >> H >> W;
    vector<string> S(H);
    for (int i = 0; i < H; i++)cin >> S[i];

    vector<vector<vector<int>>> pre(H, vector<vector<int>>(W, vector<int>(4, -1)));//復元のために、直前のマスでどっちの方向から入ってきたかを記録する

    queue<state> q;

    int sx, sy;
    for (int i = 0; i < H; i++)for (int j = 0; j < W; j++)if (S[i][j] == 'S')sx = i, sy = j;

    for (int d = 0; d < 4; d++) {
        int nx = sx + dx[d], ny = sy + dy[d];
        if (nx < 0 || ny < 0 || H <= nx || W <= ny)continue;
        if (S[nx][ny] == '#')continue;

        pre[nx][ny][d] = d;
        q.push((state) { nx, ny, d });
    }


    while (!q.empty()) {
        auto [x, y, d] = q.front(); q.pop();

        if (S[x][y] == 'G') {
            //ゴールなので復元する
            int px = x, py = y, pd = d;
            string dir = "DRUL", ans = "";
            while (px != sx || py != sy) {
                ans += dir[pd];
                int memo = pd;
                pd = pre[px][py][pd];
                px -= dx[memo];
                py -= dy[memo];
            }

            reverse(ans.begin(), ans.end());

            cout << "Yes" << endl;
            cout << ans << endl;
            return 0;
        }

        for (int nd = 0; nd < 4; nd++) {
            if (S[x][y] == 'o' && d != nd)continue;
            if (S[x][y] == 'x' && d == nd)continue;

            int nx = x + dx[nd], ny = y + dy[nd];
            if (nx < 0 || ny < 0 || H <= nx || W <= ny)continue;
            if (S[nx][ny] == '#')continue;
            if (pre[nx][ny][nd] != -1)continue;//訪問済み

            pre[nx][ny][nd] = d;
            q.push((state) { nx, ny, nd });
        }
    }

    cout << "No" << endl;

}
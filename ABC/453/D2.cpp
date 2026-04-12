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


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int H, W; cin >> H >> W;
    vector<string> S(H);
    for (int i = 0; i < H; i++)cin >> S[i];

    int sx, sy, gx, gy;
    for (int i = 0; i < H; i++)for (int j = 0; j < W; j++) {
        if (S[i][j] == 'S')sx = i, sy = j;
        if (S[i][j] == 'G')gx = i, gy = j;
    }

    //どの方向に行ったかをマスごとに頂点倍化で持っておけばただのBFSでいける?
    vector<vector<vector<tuple<int, int, int>>>> pre(H, vector<vector<tuple<int, int, int>>>(W, vector<tuple<int, int, int>>(4, { -1,-1,-1 })));
        
    queue<tuple<int, int, int>> q;

    for (int d = 0; d < 4; d++) {
        int nx = sx + dx[d], ny = sy + dy[d];
        if (nx < 0 || H <= nx || ny < 0 || W <= ny)continue;
        if (S[nx][ny] == '#')continue;
        pre[nx][ny][d] = { sx,sy,-1 };
        q.push({ nx,ny,d });
    }

    vector<int> ans;

    while (!q.empty()) {
        auto [x, y, d] = q.front(); q.pop();

        if (x == gx && y == gy) {
            //復元を行う
            while (x != sx || y != sy) {
                ans.push_back(d);
                auto p = pre[x][y][d];
                x = get<0>(p);
                y = get<1>(p);
                d = get<2>(p);
            }

            //みかんせい！！！あとで書く！！
            string s = "";
            int n = ans.size();
            for (int i = n - 1; i >= 0; i--) {
                char c;
                if (ans[i] == 0)s += 'D';
                else if (ans[i] == 1) s += 'R';
                else if (ans[i] == 2) s += 'U';
                else s += 'L';
                
            }

            cout << "Yes" << endl;
            cout << s << endl;
            return 0;
        }

        if (S[x][y] == '.') {
            //なんでもOK
            for (int nd = 0; nd < 4; nd++) {
                int nx = x + dx[nd], ny = y + dy[nd];
                if (nx < 0 || H <= nx || ny < 0 || W <= ny)continue;
                if (S[nx][ny] == '#')continue;
                if (get<0>(pre[nx][ny][nd]) != -1)continue;
                pre[nx][ny][nd] = { x,y,d };
                q.push({ nx, ny, nd });
            }
        }
        else if (S[x][y] == 'o') {
            //同じ方向
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || H <= nx || ny < 0 || W <= ny)continue;
            if (S[nx][ny] == '#')continue;
            if (get<0>(pre[nx][ny][d]) != -1)continue;
            
            pre[nx][ny][d] = { x,y,d };
            q.push({ nx, ny, d });
        }
        else if (S[x][y] == 'x') {
            //別方向
            for (int nd = 0; nd < 4; nd++) {
                if (nd == d)continue;
                int nx = x + dx[nd], ny = y + dy[nd];
                if (nx < 0 || H <= nx || ny < 0 || W <= ny)continue;
                if (S[nx][ny] == '#')continue;
                if (get<0>(pre[nx][ny][nd]) != -1)continue;
                
                pre[nx][ny][nd] = { x,y,d };
                q.push({ nx, ny, nd });
            }
        }
    }

    cout << "No" << endl;
}
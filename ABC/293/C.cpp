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

//cin.tie(nullptr);
//ios::sync_with_stdio(false);

int H, W;

void dfs(int x, int y, vector<vector<int>>& A, int& ans, vector<int>& path) {
    if (x == H - 1 && y == W - 1) {
        set<int> st;
        for (int i = 0; i < path.size(); i++) {
            if (st.count(path[i]))return;
            st.insert(path[i]);
        }

        ans++;
        return;
    }

    int nx = x + 1, ny = y + 1;
    if (nx < H) {
        path.push_back(A[nx][y]);
        dfs(nx, y, A, ans, path);
        path.pop_back();
    }

    if (ny < W) {
        path.push_back(A[x][ny]);
        dfs(x, ny, A, ans, path);
        path.pop_back();
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> H >> W;
    vector<vector<int>> A(H, vector<int>(W));
    for (int i = 0; i < H; i++)for (int j = 0; j < W; j++)cin >> A[i][j];

    //ありうる（最短）経路は20C10通りで全然いける

    vector<int> path;

    int ans = 0;
    path.push_back(A[0][0]);
    dfs(0, 0, A, ans, path);

    cout << ans << endl;
}
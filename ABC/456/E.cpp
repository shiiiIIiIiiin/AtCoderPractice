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

ll dx[] = { 1, 0, -1, 0 }, dy[] = { 0, 1, 0, -1 };
const ll INF = LLONG_MAX / 2;




bool dfs(vector<vector<int>>& G, int v, vector<bool>& seen, vector<bool>& finished) {

    /*
　　　https://drken1215.hatenablog.com/entry/2023/05/20/200517
　　　から持ってきた
　　

    seen[v] = true;    // 行きがけ時に true になる
    for (const Edge& e : G[v]) {
        int v2 = (辺 e の行き先の頂点);
        if (v2 が逆戻りの場合) continue;  // 無向グラフの場合は必要

        // 頂点 v2 がすでに探索済みの場合はスキップ 
        if (finished[v2]) continue;

        // サイクル検出
        if (seen[v2] && !finished[v2]) return true;

        // 頂点 v2 を再帰的に探索
        if (dfs(G, v2, seen, finished)) return true;
    }
    finished[v] = true;  // 帰りがけ時に true になる
    return false;
   */

    seen[v] = true;    // 行きがけ時に true になる
    for (auto e : G[v]) {
        int v2 = e;
        // 頂点 v2 がすでに探索済みの場合はスキップ 
        if (finished[v2]) continue;

        // サイクル検出
        if (seen[v2] && !finished[v2]) return true;

        // 頂点 v2 を再帰的に探索
        if (dfs(G, v2, seen, finished)) return true;
    }
    finished[v] = true;  // 帰りがけ時に true になる
    return false;

}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    //Wが小さい、頂点倍化で出来そう

    /*
    曜日wの都市nの状態を持つ頂点を　N*w+n にする
    */

    int T; cin >> T;

    for (; T--;) {
        int N, M; cin >> N >> M;
        vector<vector<int>> memo(N);
        for (int i = 0; i < M; i++) {
            int u, v; cin >> u >> v;
            u--;
            v--;
            memo[u].push_back(v);
            memo[v].push_back(u);
        }

        int W; cin >> W;
        vector<string> S(N);
        for (int i = 0; i < N; i++)cin >> S[i];

        vector<vector<int>> G(N * W);

        for (int w = 0; w < W; w++) {
            for (int n = 0; n < N; n++) {
                int pos = N * w + n;
                if (S[n][w] == 'x')continue;
                for (auto v : memo[n]) {
                    int nex = N * ((w + 1) % W) + v;
                    if (S[v][(w + 1) % W] == 'o')G[pos].push_back(nex);
                }

                if (S[n][(w + 1) % W] == 'o')G[pos].push_back(N * ((w + 1) % W) + n);
            }
        }

        //Gの中にサイクルがあればOK
        bool f = false;
        vector<bool> seen(N * W), finished(N * W);

        for (int i = 0; i < N; i++) {
            if (S[i][0] == 'x')continue;
            if (seen[i])continue;

            if (dfs(G, i, seen, finished)) {
                f = true;
                break;
            }
        }

        cout << (f ? "Yes" : "No") << endl;
    }
}
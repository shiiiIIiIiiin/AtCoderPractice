#include<bits/stdc++.h>
using namespace std;

class UnionFind {
public:
    vector<vector<int>> siz;
    vector<vector<pair<int, int>>> par;

    UnionFind(int H, int W) {
        siz.resize(H + 1);
        par.resize(H + 1);

        for (int i = 0; i <= H; i++) {
            siz[i].resize(W + 1, 1);
            par[i].resize(W + 1, make_pair(-1, -1));  // サイズ修正
        }
    }

    // 根を求める
    pair<int, int> root(int x, int y) {
        while (par[x][y].first != -1 || par[x][y].second != -1) {
            int newX = par[x][y].first;
            int newY = par[x][y].second;
            x = newX;
            y = newY;
        }
        return make_pair(x, y);
    }

    // 統合する
    void unite(int u, int u1, int v, int v1) {
        int RUx = root(u, u1).first;
        int RUy = root(u, u1).second;
        int RVx = root(v, v1).first;
        int RVy = root(v, v1).second;

        if (RUx == RVx && RUy == RVy) return;

        if (siz[RUx][RUy] < siz[RVx][RVy]) {
            par[RUx][RUy] = {RVx, RVy};
            siz[RVx][RVy] += siz[RUx][RUy];
        } else {
            par[RVx][RVy] = {RUx, RUy};
            siz[RUx][RUy] += siz[RVx][RVy];
        }
    }

    // 結合判定をする
    bool same(int u, int u1, int v, int v1) {
        return root(u, u1) == root(v, v1);
    }
};

int main() {
    int H, W, Q; cin >> H >> W >> Q;
    UnionFind UF(H, W);
    bool F[H + 1][W + 1] = {};
    int dx[] = {-1, 0, 1, 0}, dy[] = {0, -1, 0, 1};

    for (int i = 0; i < Q; i++) {
        int q; cin >> q;

        if (q == 1) {
            int r, c; cin >> r >> c;
            F[r][c] = true;

            for (int j = 0; j < 4; j++) {
                int nr = r + dx[j];
                int nc = c + dy[j];
                if (1 <= nr && nr <= H && 1 <= nc && nc <= W && F[nr][nc]) {
                    UF.unite(r, c, nr, nc);
                }
            }
        } else {
            int ra, ca, rb, cb; cin >> ra >> ca >> rb >> cb;
            if (F[ra][ca] && F[rb][cb] && UF.same(ra, ca, rb, cb)) cout << "Yes" << endl;
            else cout << "No" << endl;
        }
    }
}
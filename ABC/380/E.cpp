#include <bits/stdc++.h>
using namespace std;

class UnionFind {
public:
    vector<int> col, par, siz, cnt, left;

    UnionFind(int n) {
        col.resize(n + 1); par.resize(n + 1, -1);
        siz.resize(n + 1, 1); cnt.resize(n + 1, 1); left.resize(n + 1);
        for (int i = 0; i <= n; i++) { col[i] = i; left[i] = i; }
    }

    int root(int x) {
        if (par[x] == -1) return x;
        return par[x] = root(par[x]); // 経路圧縮を適用
    }

    void unite(int x, int y) {
        int rx = root(x), ry = root(y);
        if (rx == ry) return;

        if (siz[rx] < siz[ry]) swap(rx, ry);
        par[ry] = rx; siz[rx] += siz[ry];
        left[rx] = min(left[rx], left[ry]); // 常に左端のインデックスを保持
    }

    int getcol(int x) { return col[root(x)]; }

    void changecol(int x, int c) {
        int rx = root(x);
        cnt[col[rx]] -= siz[rx];
        col[rx] = c; cnt[c] += siz[rx];
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); // 高速化
    int N, Q; cin >> N >> Q;
    UnionFind uf(N);

    for (; Q--;) {
        int q; cin >> q;
        if (q == 1) {
            int x, c; cin >> x >> c;
            if (uf.getcol(x) == c) continue;

            uf.changecol(x, c);
            
            // 左隣のチェック
            int cur_l = uf.left[uf.root(x)];
            if (cur_l - 1 >= 1 && uf.getcol(cur_l - 1) == c) uf.unite(cur_l - 1, x);

            // 右隣のチェック（左と合体した可能性があるので情報を再取得）
            int rx = uf.root(x);
            int L = uf.left[rx], S = uf.siz[rx];
            if (L + S <= N && uf.getcol(L + S) == c) uf.unite(x, L + S);
        }
        else {
            int c; cin >> c;
            cout << uf.cnt[c] << endl;
        }
    }
}
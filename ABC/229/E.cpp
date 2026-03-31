#include<bits/stdc++.h>
using namespace std;

class UnionFind{
  public:
    vector<int> par;
    vector<int> siz;
    
    UnionFind(int n){
      par.resize(n+1,-1);
      siz.resize(n+1,1);
    }
    
    int root(int x){
      if(par[x] == -1) return x;  // 自分が根の場合
      return par[x] = root(par[x]);  // パス圧縮
    }
    
    void unite(int x, int y){
      int rx = root(x), ry = root(y);
      if(rx == ry) return;  // すでに同じ連結成分なら何もしない
      
      // 大きい方の木に小さい方を繋げる
      if(siz[rx] < siz[ry]){
        par[rx] = ry;
        siz[ry] += siz[rx];
      } else {
        par[ry] = rx;
        siz[rx] += siz[ry];
      }
    }
    
    bool same(int x, int y){
      return root(x) == root(y);
    }
};


int main(){
  int N, M;
  cin >> N >> M;
  UnionFind uf(N);
  vector<vector<int>> G(N+1);
  
  for(int i = 0; i < M; i++){
    int a, b;
    cin >> a >> b;
    G[a].push_back(b);
    G[b].push_back(a);
  }
  
  vector<int> ans(N+1, 0);
  int components = 0;  // 現在の連結成分の数
  
  // 頂点iを1つずつ追加していく
  for(int i = N; i > 0; i--){
    components++;  // 頂点iを追加するので連結成分が1つ増える
    
    for(int j = 0; j < G[i].size(); j++){
      if(G[i][j] > i && !uf.same(i, G[i][j])) {
        uf.unite(i, G[i][j]);
        components--;  // 新しい辺を追加して2つの連結成分が1つになる
      }
    }
    
    ans[i-1] = components;  // 現在の連結成分数を記録
  }
  
  for(int i = 1; i <= N; i++){
    cout << ans[i] << endl;  // 各ステップでの連結成分数を出力
  }
}
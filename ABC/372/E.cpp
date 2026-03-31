#include <bits/stdc++.h>
using namespace std;

class UnionFind{
  public:
   vector<int> par;
   vector<int> siz;
   vector<vector<int>> ranking;
   
   UnionFind(int n){
     par.resize(n+1,-1);
     siz.resize(n+1,1);
     ranking.resize(n+1);
     
     for(int i=0;i<n+1;i++){
       ranking[i].resize(10);
       for(int j=0;j<10;j++)ranking[i][j]=-1;
       ranking[i][0]=i;
     }
   }
   
   int root(int x){
     if(par[x]==-1)return x;
     else return par[x]=root(par[x]);
   }
   
   void mix(vector<int> &a,vector<int> &b){
     vector<int> memo(20);
     for(int i=0;i<10;i++)memo[i]=a[i];
     for(int i=10;i<20;i++)memo[i]=b[i-10];
     
     sort(memo.begin(),memo.end());
     
     for(int i=0;i<10;i++)a[i]=memo[19-i];
     
   }
   
   void unite(int x,int y){
     int rx=root(x),ry=root(y);
     if(rx==ry)return;
     
     if(siz[rx]<siz[ry]){
       par[rx]=ry;
       siz[ry]+=siz[rx];
       mix(ranking[ry],ranking[rx]);
     }else{
       par[ry]=rx;
       siz[rx]+=siz[ry];
       mix(ranking[rx],ranking[ry]);
     }
     
     
   }
   
   
};

int main(){
  int N,Q;cin>>N>>Q;
  UnionFind uf(N);
  
  for(int i=0;i<Q;i++){
    int q;cin>>q;
    
    if(q==1){
      int u,v;cin>>u>>v;
      uf.unite(u,v);
    }
    else{
      int v,k;cin>>v>>k;
      cout<<uf.ranking[uf.root(v)][k-1]<<endl;
    }
    
    
  }
  
  return 0;
}
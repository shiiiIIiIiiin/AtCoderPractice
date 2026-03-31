#include<bits/stdc++.h>
using namespace std;

class UnionFind{
  
  public:
  vector<int> par;//親の番号
  vector<int> size;//size[x]　頂点xが含まれるグループの大きさ
  
  UnionFind(int N){
    for(int i=0;i<=N;i++){
      par.push_back(-1);//par[x]==-1　xは根っこ
      size.push_back(1);
    }
  }
  
  //根を求める関数(クエリ2)
  int root(int x){
    while(true){
      if(par[x]==-1)break;
      x=par[x];
    }
    return x;
  }


  //連結させる(クエリ1)
  void unite(int u,int v){
    int RU=root(u),RV=root(v);
    
    if(RU==RV)return;//なんでこれを忘れるとTLEになるのかがわからない
    
    
    if(size[RU]>=size[RV]){
      par[RV]=RU;
      size[RU]+=size[RV];
    }else{
      par[RU]=RV;
      size[RV]+=size[RU];
    }
    return;
  }

};

int main(){
  int N,Q;cin>>N>>Q;
  
  UnionFind UF(N);
  
  for(int i=0;i<Q;i++){
    int que,u,v;cin>>que>>u>>v;
    if(que==1){
      UF.unite(u,v);
    }else{
      cout<<(UF.root(u)==UF.root(v)?"Yes":"No")<<endl;
    }
  }
  return 0;
}
#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,K;cin>>N>>K;
  vector<vector<int>> G(N+1);
  for(int i=0;i<N-1;i++){
    int a,b;cin>>a>>b;
    G[a].push_back(b);
    G[b].push_back(a);
  }

  vector<bool> sitei(N+1,false);
  int v;
  for(int i=0;i<K;i++){
    cin>>v;
    sitei[v]=true;
  }

  vector<bool> visited(N+1,false),cut(N+1,true);

   auto dfs=[&](auto dfs,int pos,int pre)->void{
    visited[pos]=true;
    if(sitei[pos])cut[pos]=false;

    for(auto x:G[pos]){//自分の子をすべて見て、下に指定された頂点があるか確認している
      if(x!=pre) dfs(dfs,x,pos);
      else continue;
      
      if(!cut[x])cut[pos]=false;
    }
    return;
  };

  dfs(dfs,v,-1);

  int ans=0;

  for(int i=1;i<=N;i++)if(!cut[i])ans++;

  cout<<ans<<endl;
  
}
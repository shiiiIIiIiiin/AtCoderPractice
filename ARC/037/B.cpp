#include<bits/stdc++.h>
using namespace std;

int N,M;
int ans=0;

void dfs(vector<vector<int>> &G,int pos,int pre,vector<bool> &visited,int start,bool &cycle){
  visited[pos]=true;
  
  for(int i=0;i<G[pos].size();i++){
    int nex=G[pos][i];
    if(nex==pre)continue;
    
    if(visited[nex]){
      //サイクルがあった
      cycle=true;
      //continue;
      return;
    }
    
    dfs(G,nex,pos,visited,start,cycle);
  }
  
  if(pos==start&&!cycle)ans++;
  
  return;
}


int main(){
  cin>>N>>M;
  vector<vector<int>> G(N+1);
  for(int i=0;i<M;i++){
    int u,v;cin>>u>>v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  
  vector<bool> visited(N+1,false);
  
  for(int i=1;i<=N;i++){
    bool cycle=false;
    if(!visited[i])dfs(G,i,-1,visited,i,cycle);
  }
  cout<<ans<<endl;
}
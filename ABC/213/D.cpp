#include<bits/stdc++.h>
using namespace std;

void dfs(int pos,int pre,vector<vector<int>> &G,vector<bool> &visited){
  visited[pos]=true;
  cout<<pos<<" ";
  
  for(int i=0;i<G[pos].size();i++){
    int nex=G[pos][i];
    if(visited[nex])continue;
    dfs(nex,pre,G,visited);
    cout<<pos<<" ";
  }
  
}

int main(){
  int N;cin>>N;
  vector<vector<int>> G(N+1);
  for(int i=0;i<N-1;i++){
    int a,b;cin>>a>>b;
    G[a].push_back(b);
    G[b].push_back(a);
  }
  
  for(int i=1;i<=N;i++)sort(G[i].begin(),G[i].end());
  
  vector<bool> visited(N+1,false);
  
  dfs(1,-1,G,visited);
  
}
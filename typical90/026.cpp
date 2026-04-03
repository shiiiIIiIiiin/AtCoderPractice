#include<bits/stdc++.h>
using namespace std;

void dfs(int pos,bool pre,vector<int> &kuro,vector<int> &siro,vector<vector<int>> &G,vector<bool> &visited){
  visited[pos]=true;
  if(pre)kuro.push_back(pos);
  else siro.push_back(pos);
  
  for(int i=0;i<G[pos].size();i++){
    int nex=G[pos][i];
    if(visited[nex])continue;
    
    dfs(nex,!pre,kuro,siro,G,visited);
  }
  
  return;
}

int main(){
  int N;
  cin>>N;
  vector<vector<int>> G(N+1);
  
  for(int i=0;i<N-1;i++){
    int a,b;cin>>a>>b;
    G[a].push_back(b);
    G[b].push_back(a);
  }
  
  vector<int> kuro,siro;
  vector<bool> visited(N+1,false);
  bool pre=false;
  
  dfs(1,&pre,kuro,siro,G,visited);
  
  if(siro.size()<=kuro.size()){
    for(int i=0;i<N/2;i++)cout<<kuro[i]<<" ";
  }else{
    for(int i=0;i<N/2;i++)cout<<siro[i]<<" ";
  }
  cout<<endl;
  
  /*
  for(int i=0;i<kuro.size();i++)cout<<kuro[i]<<" ";
  cout<<endl;
  for(int i=0;i<siro.size();i++)cout<<siro[i]<<" ";
  */
}
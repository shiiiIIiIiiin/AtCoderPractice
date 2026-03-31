#include<bits/stdc++.h>
using namespace std;

int f(int x){
  return x*x;
}

void dfs(vector<vector<int>> &G,int pos,vector<bool> &visited){
  visited[pos]=true;
  
  for(int i=0;i<G[pos].size();i++){
    int nex=G[pos][i];
    if(visited[nex])continue;
    
    dfs(G,nex,visited);
  }
  
  return;
}

int main(){
  int N,D;cin>>N>>D;
  vector<int> X(N+1),Y(N+1);
  for(int i=1;i<=N;i++)cin>>X[i]>>Y[i];
  
  vector<vector<int>> G(N+1);
  
  for(int i=1;i<=N-1;i++){
    for(int j=i+1;j<=N;j++){
      if(f(X[i]-X[j])+f(Y[i]-Y[j])<=D*D){
        G[i].push_back(j);
        G[j].push_back(i);
      }
    }
  }
  
  vector<bool> visited(N+1,false);
  
  dfs(G,1,visited);
  
  
  for(int i=1;i<=N;i++)cout<<(visited[i]?"Yes":"No")<<endl;
  
  
}
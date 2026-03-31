#include<bits/stdc++.h>
using namespace std;

long long N,M;

void dfs(vector<vector<tuple<long long,long long,long long>>> &G,vector<bool> &visited,long long pos,vector<long long> &ansX,vector<long long> &ansY){
  visited[pos]=true;
  
  for(int i=0;i<G[pos].size();i++){
    auto [nex,dx,dy]=G[pos][i];
    if(visited[nex])continue;
    
    ansX[nex]=ansX[pos]+dx;
    ansY[nex]=ansY[pos]+dy;
    
    dfs(G,visited,nex,ansX,ansY);
  }
}

int main(){
  cin>>N>>M;
  vector<long long> A(M),B(M),X(M),Y(M),ansX(N+1,LLONG_MAX),ansY(N+1,LLONG_MAX);
  vector<vector<tuple<long long,long long,long long>>> G(N+1);
  for(int i=0;i<M;i++){
    cin>>A[i]>>B[i]>>X[i]>>Y[i];
    G[A[i]].push_back({B[i],X[i],Y[i]});
    G[B[i]].push_back({A[i],-X[i],-Y[i]});
  }
  vector<bool> visited(N+1,false);
  
  ansX[1]=ansY[1]=0;
  dfs(G,visited,(long long)1,ansX,ansY);
  
  for(int i=1;i<=N;i++){
    if(ansX[i]!=LLONG_MAX)cout<<ansX[i]<<" "<<ansY[i]<<endl;
    else cout<<"undecidable"<<endl;
  }
  
}
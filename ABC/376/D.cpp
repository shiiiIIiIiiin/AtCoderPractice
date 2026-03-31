#include <bits/stdc++.h>
using namespace std;

int main(){
  int N,M;cin>>N>>M;
  vector<vector<int>> G(N+1);
  for(int i=0;i<M;i++){
    int a,b;cin>>a>>b;
    G[a].push_back(b);
  }
  
  vector<int> dist(N+1,-1);
  queue<int> que;
  
  dist[1]=0;
  que.push(1);
  
  while(!que.empty()){
    int pos=que.front();que.pop();
    
    for(int i=0;i<G[pos].size();i++){
      int nex=G[pos][i];
      if(dist[nex]!=-1)continue;
      
      dist[nex]=dist[pos]+1;
      
      que.push(nex);
    }
    
  }
  
  set<int> s;
  for(int i=1;i<=N;i++){
    for(int j=0;j<G[i].size();j++)if(G[i][j]==1)s.insert(i);
  }
  
  int ans=INT_MAX;
 
  for(auto x:s)if(dist[x]!=-1)ans=min(ans,dist[x]);
  
  cout<<(ans==INT_MAX ? -1:ans+1)<<endl;
  
  return 0;
}
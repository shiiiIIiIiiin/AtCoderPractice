#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  vector<vector<int>> G(N+1);
  for(int i=0;i<N-1;i++){
    int u,v;cin>>u>>v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  
  vector<int> ans;
  int cnt=0;
  for(int i=1;i<=N;i++)if(G[i].size()>=3){
    ans.push_back(G[i].size());
    cnt+=G[i].size()+1;
  }
  
  for(int i=0;i<(N-cnt)/3;i++)ans.push_back(2);
  
  sort(ans.begin(),ans.end());
  
  for(auto x:ans)cout<<x<<" ";
  cout<<endl;
}
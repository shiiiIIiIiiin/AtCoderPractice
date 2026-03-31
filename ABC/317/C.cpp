#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,M;cin>>N>>M;
  vector<vector<int>> G(N+1,vector<int>(N+1,-1));
  for(int i=0;i<M;i++){
    int a,b,c;cin>>a>>b>>c;
    G[a][b]=c;
    G[b][a]=c;
  }
  
  vector<int> P(N);
  for(int i=0;i<N;i++)P[i]=i+1;
  
  int ans=-1;
  
  do{
    int memo=0;
    bool can=true;
    for(int i=0;i<N-1;i++){
      if(G[P[i]][P[i+1]]==-1)break;
      memo+=G[P[i]][P[i+1]];
    }
    
    ans=max(ans,memo);
    
  }while(next_permutation(P.begin(),P.end()));
  
  cout<<ans<<endl;
}
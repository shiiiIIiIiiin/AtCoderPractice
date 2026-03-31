#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,M;cin>>N>>M;
  vector<vector<bool>> A(M,vector<bool>(N,false));
  for(int i=0;i<M;i++){
    int c;cin>>c;
    for(int j=0;j<c;j++){
      int k;cin>>k;
      k--;
      A[i][k]=true;
    }
  }
  
  int ans=0;
  
  for(int i=0;i<1<<M;i++){//bit全探索
    vector<bool> can(N,false);
    
    for(int j=0;j<M;j++){
      if(i&(1<<j)){
        for(int k=0;k<A[j].size();k++)if(A[j][k])can[k]=true;
      }
    }
    
    bool res=true;
    
    for(int j=0;j<N;j++)if(!can[j])res=false;
    
    if(res)ans++;
  }
  
  cout<<ans<<endl;
  
}
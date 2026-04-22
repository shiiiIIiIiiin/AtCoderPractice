#include<bits/stdc++.h>
using namespace std;
int main(){
  int N,W;
  cin>>N>>W;
  
  long int w[N+1],v[N+1],i,j;
  for(i=1;i<=N;i++)cin>>w[i]>>v[i];
  
  long int dp[N+1][W+1];
  
  for(i=0;i<N+1;i++){
    for(j=0;j<W+1;j++){
      dp[i][j]=0;
    }
  }
  
 for(i=1;i<N+1;i++){
   for(j=1;j<W+1;j++){
     
     if(j-w[i]>=0){
     dp[i][j]=max(dp[i-1][j],dp[i-1][j-w[i]]+v[i]);
     }else{
       dp[i][j]=dp[i-1][j];
     }
   }
 }
  
  cout<<dp[N][W]<<endl;
}
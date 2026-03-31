#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,i,j;
  string S;
  cin>>N>>S;
  
  string memo="atcoder";
  
  int dp[8][N+1];
  for(i=0;i<=7;i++)for(j=0;j<=N;j++)dp[i][j]=0;
  
  for(i=1;i<N+1;i++){
    if(S[i-1]=='a')dp[1][i]+=dp[1][i-1]+1;
    else dp[1][i]=dp[1][i-1];
  }
  
  
  for(i=2;i<=7;i++)for(j=1;j<=N;j++){
    //dp[i][j]を埋める
    
    if(S[j-1]==memo[i-1])dp[i][j]=dp[i-1][j-1];
    
    dp[i][j]+=dp[i][j-1];
    dp[i][j]%=1'000'000'007;
  }
  
  /*
  for(i=0;i<=7;i++){
    for(j=0;j<=N;j++){
      cout<<dp[i][j]<<"  ";
    }
    cout<<endl;
  }
  */
  cout<<dp[7][N]<<endl;
  
  
}
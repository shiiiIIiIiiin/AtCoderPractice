#include<bits/stdc++.h>
using namespace std;

int main(){
  string S,T;
  cin>>S;
  cin>>T;
  
  int N=S.size(),M=T.size();
  
  int dp[N+1][M+1],i,j;
  for(i=0;i<N+1;i++){
    for(j=0;j<M+1;j++){
      dp[i][j]=0;
    }
  }
  
  for(i=1;i<N+1;i++){
    for(j=1;j<M+1;j++){
      if(S[i-1]==T[j-1]){          //文字一緒だったら
        dp[i][j]=max({dp[i][j-1],dp[i-1][j],dp[i-1][j-1]+1});
      }else{
        dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
      }
    }
  }
  
  cout<<dp[N][M]<<endl;

}
#include<bits/stdc++.h>
using namespace std;

int main(){
  long long X,Y,Z;cin>>X>>Y>>Z;
  string S;cin>>S;
  long long dp[2][S.size()+1];
  long long N=S.size();
  //dp[0][k]...k文字目までやったときにCapがoffとなる最小時間
  
  dp[0][0]=0;
  dp[1][0]=10000000000;
  
  for(int i=1;i<N+1;i++){
    if(S[i-1]=='A'){//大文字にしたいなら
      dp[0][i]=min(dp[0][i-1]+Y,dp[1][i-1]+Z+Y);
      dp[1][i]=min(dp[1][i-1]+X,dp[0][i-1]+Z+X);
    }
    else{
      dp[0][i]=min(dp[0][i-1]+X,dp[1][i-1]+Z+X);
      dp[1][i]=min(dp[1][i-1]+Y,dp[0][i-1]+Z+Y);
    }
  }
  
  cout<<min(dp[0][N],dp[1][N])<<endl;
 
 /*
  for(int i=0;i<2;i++){
    for(int j=0;j<N+1;j++)cout<<dp[i][j]<<" ";
    cout<<endl;
  }
  */
}
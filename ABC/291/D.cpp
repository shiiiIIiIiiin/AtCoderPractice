#include <bits/stdc++.h>
using namespace std;
#define MOD 998244353

int main(){
  int N;cin>>N;
  vector<int> A(N+1),B(N+1);
  for(int i=1;i<=N;i++)cin>>A[i]>>B[i];
  
  vector<vector<long long>> dp(2,vector<long long>(N+1,0));
  
  dp[0][0]=dp[1][0]=0;//dp[0(1)][k]...k番目が表(裏)であり条件を満たす裏返し方
  dp[0][1]=1;
  dp[1][1]=1;
  
  for(int i=2;i<=N;i++){
    dp[0][i]=((A[i-1]!=A[i] ? dp[0][i-1]:0)+(B[i-1]!=A[i] ? dp[1][i-1]:0))%MOD;
    dp[1][i]=((A[i-1]!=B[i] ? dp[0][i-1]:0)+(B[i-1]!=B[i] ? dp[1][i-1]:0))%MOD;
  }
  
  cout<<(dp[0][N]+dp[1][N])%MOD<<endl;
  
  /*
  for(int i=0;i<2;i++){
    for(int j=0;j<=N;j++)cout<<dp[i][j]<<" ";
    cout<<endl;
  }
  */
}
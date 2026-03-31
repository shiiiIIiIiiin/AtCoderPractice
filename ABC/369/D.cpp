#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;cin>>N;
  int A[N+1];
  for(int i=1;i<=N;i++)cin>>A[i];
  
  long long dp[2][N+1];
  dp[0][0]=0;
  dp[1][0]=-1'000'000'000'000;
  
  for(int i=1;i<=N;i++){
    dp[0][i]=max(dp[0][i-1],dp[1][i-1]+2*A[i]);
    dp[1][i]=max(dp[0][i-1]+A[i],dp[1][i-1]);
  }
  
  cout<<max(dp[0][N],dp[1][N])<<endl;
  
}
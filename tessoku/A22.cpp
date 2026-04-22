#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;
  cin>>N;
  int i,A[N],B[N];
  for(i=1;i<=N-1;i++)cin>>A[i];
  for(i=1;i<=N-1;i++)cin>>B[i];
  
  int dp[N+1];
  
  dp[1]=0;
  for(i=2;i<=N;i++)dp[i]=-150;
  
  for(i=1;i<N;i++){
    dp[A[i]]=max(dp[A[i]],dp[i]+100);
    dp[B[i]]=max(dp[B[i]],dp[i]+150);
  }
  cout<<dp[N]<<endl;
}
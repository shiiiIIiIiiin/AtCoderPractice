#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  vector<int> X(N+1),Y(N+1);
  for(int i=1;i<=N;i++)cin>>X[i]>>Y[i];
  
  vector<vector<long long>> dp(2,vector<long long>(N+1,-100000000000));
  dp[0][0]=0;
  
  for(int i=1;i<=N;i++){
    if(X[i]==0){
      dp[0][i]=max(dp[0][i-1]+Y[i],max(dp[1][i-1]+Y[i],dp[0][i-1]));
      dp[1][i]=dp[1][i-1];
    }
    else{
      dp[0][i]=dp[0][i-1];
      dp[1][i]=max(dp[0][i-1]+Y[i],dp[1][i-1]);
    }
  }
  cout<<max(dp[0][N],dp[1][N])<<endl;
}
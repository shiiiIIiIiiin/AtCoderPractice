#include<bits/stdc++.h>
using namespace std;
#define MOD 1000000007

int main(){
  int K;cin>>K;
  if(K%9!=0){
    cout<<0<<endl;
    return 0;
  }
  
  long long dp[K+2];
  for(int i=0;i<=K+1;i++)dp[i]=0;
  dp[1]=1;
  
  for(int i=2;i<=K+1;i++){
    
    for(int j=1;j<=9;j++){
      if(i-j<0)continue;
      dp[i]+=dp[i-j];
      if(dp[i]>MOD)dp[i]-=MOD;
    }
    
  }
  
  cout<<dp[K+1]<<endl;
}
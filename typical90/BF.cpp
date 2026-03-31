#include<bits/stdc++.h>
using namespace std;

int main(){
  long long N,K;cin>>N>>K;
  
  int dp[60][100'000];
  for(int i=0;i<60;i++)for(int j=0;j<100000;j++)dp[i][j]=0;
  
  for(int i=0;i<100000;i++){
    long long copy=i,cnt=i;
    while(copy!=0){
      cnt+=copy%10;
      copy/=10;
    }
    dp[0][i]=cnt%100000;
  }
  
  for(int i=1;i<60;i++){
    for(int j=0;j<100000;j++){
      dp[i][j]=dp[i-1][dp[i-1][j]];
    }
  }
  
  int ans=N,scale=0;
  
  while(K!=0){
    if(K%2==1)ans=dp[scale][ans];
    K/=2;
    scale++;
  }
  
  cout<<ans<<endl;
}
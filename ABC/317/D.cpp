#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
  int N;cin>>N;
  vector<int> X(N+1),Y(N+1),Z(N+1);
  for(int i=1;i<=N;i++)cin>>X[i]>>Y[i]>>Z[i];
  
  vector<int> change(N+1);//change[i]...選挙区iをとるのに必要な鞍替え人数
  for(int i=1;i<=N;i++)change[i]=max(0,(X[i]+Y[i]+1)/2-X[i]);
  
  ll cnt=0;
  for(int i=1;i<=N;i++)cnt+=Z[i];
  
  vector dp(N+1,vector<ll>(cnt+1,LLONG_MAX/2));//dp[i][j]...選挙区iまでを使ってｊ議席得るために必要な最小鞍替え数
  
  cnt=cnt/2+1;
  
  for(int i=1;i<=N;i++)if(X[i]>Y[i])cnt-=Z[i];
  cnt=max((ll)0,cnt);
  
  if(cnt==0){
    cout<<0<<endl;
    return 0;
  }
  
  
  for(int i=0;i<=N;i++)dp[i][0]=0;
  
  for(int i=1;i<=N;i++){
    for(int j=1;j<dp[0].size();j++){
      
      if(j-Z[i]>=0&&change[i]!=0)dp[i][j]=min(dp[i-1][j-Z[i]]+change[i],dp[i-1][j]);
      else dp[i][j]=dp[i-1][j];
      
    }
  }
  
  long long ans=LLONG_MAX;
  
  for(int i=cnt;i<dp[0].size();i++){
    if(dp[N][i]<LLONG_MAX/2){
      ans=min(ans,dp[N][i]);
    }
  }
  
  cout<<ans<<endl;
  
  /*
 for(int j=0;j<=dp[0].size();j++){
    if(dp[N][j]==86)cout<<"86:"<<N<<"  "<<j<<endl;
    if(dp[N][j]==334)cout<<"334:"<<N<<"  "<<j<<endl;
  }
  */
}
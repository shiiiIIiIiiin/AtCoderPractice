#include<bits/stdc++.h>
#include<atcoder/all>
using namespace atcoder;
using namespace std;

int N,X;

bool ingrid(int x){
  return 0<=x&&x<=X;
}

int main(){
  cin>>N>>X;
  vector<int> a(N+1),b(N+1);
  for(int i=1;i<=N;i++)cin>>a[i]>>b[i];
  
  vector<vector<bool>> dp(N+1,vector<bool>(X+1,false));
  dp[0][0]=true;
  
  for(int i=1;i<=N;i++){
    for(int j=0;j<=X;j++){
      
      if(ingrid(j-a[i])){
        if(dp[i-1][j-a[i]])dp[i][j]=true;
      }
      
      if(ingrid(j-b[i])){
        if(dp[i-1][j-b[i]])dp[i][j]=true;
      }
    }
  }
 
 /* 
  for(int i=0;i<=N;i++){
    for(int j=0;j<=X;j++)cout<<dp[i][j]<<" ";
    cout<<endl;
  }
  */
  
  cout<<(dp[N][X] ? "Yes":"No")<<endl;
}
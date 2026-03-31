#include<bits/stdc++.h>
using namespace std;

int main(){
  long long N,K;cin>>N>>K;
  int X[N],A[N];
  for(int i=0;i<N;i++)cin>>X[i];
  for(int i=0;i<N;i++)cin>>A[i];
  
  long long dp[60][N+1];
  
  for(int i=1;i<=N;i++)dp[0][i]=X[i-1];
  
  for(int i=1;i<60;i++){
    for(int j=1;j<=N;j++)dp[i][j]=dp[i-1][dp[i-1][j]];
  }
  
  for(int i=0;i<N;i++){
    int pos=i+1;
    
    for(int j=59;j>=0;j--){
      if((K/(1LL<<j))%2==1)pos=dp[j][pos];
    }
    
    cout<<A[pos-1]<<" ";
    
  }
  
  cout<<endl;
  return 0;
  
}
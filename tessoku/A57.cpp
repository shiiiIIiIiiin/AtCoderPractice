#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,Q;cin>>N>>Q;
  vector<int> A(N),X(Q),Y(Q);
  for(int i=0;i<N;i++)cin>>A[i];
  for(int i=0;i<Q;i++)cin>>X[i]>>Y[i];
  
  long long dp[30][N+1];
  
  for(int i=1;i<=N;i++)dp[0][i]=A[i-1];
  
  for(int i=1;i<30;i++){
    for(int j=1;j<=N;j++){
      dp[i][j]=dp[i-1][dp[i-1][j]];
    }
  }
  
  for(int i=0;i<Q;i++){
    int pos=X[i];
    
    for(int d=29;d>=0;d--){
      if((Y[i]/(1<<d))%2==1)pos=dp[d][pos];
    }
    cout<<pos<<endl;
  }
  
  return 0;
  
}
#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  vector<long long> Q(N),A(N),B(N);
  for(int i=0;i<N;i++)cin>>Q[i];
  for(int i=0;i<N;i++)cin>>A[i];
  for(int i=0;i<N;i++)cin>>B[i];
  
  long long ans=0;
  
  for(int i=0;i<=1000000;i++){//Aをi個作る
    bool can=true;
    for(int j=0;j<N;j++){
      if(Q[j]<A[j]*i)can=false;
    }
    
    long long M=LLONG_MAX;
    
    for(int j=0;j<N;j++){
      if(B[j]==0)continue;
      M=min(M,(Q[j]-A[j]*i)/B[j]);
    }
    
    if(can)ans=max(ans,i+M);
  }
  
  cout<<ans<<endl;
}
#include <bits/stdc++.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
using ll = long long;

int main(){
  ll N,M,P;cin>>N>>M>>P;
  vector<ll> A(N),B(M);
  for(int i=0;i<N;i++)cin>>A[i];
  for(int i=0;i<M;i++)cin>>B[i];
  sort(B.begin(),B.end());
  
  vector<ll> wa(M+1);
  wa[0]=0;
  for(int i=1;i<=M;i++)wa[i]=B[i-1]+wa[i-1];
  
  
  ll ans=0;
  
  for(int i=0;i<N;i++){
    //二分探索でP<=A[i]+B[m]なら　値段はP
    
    ll id=(upper_bound(B.begin(),B.end(),P-A[i])-B.begin());
    
    //cout<<id<<endl;
    //cout<<P*(N-id)+id*A[i]+wa[id]<<endl;
    
    ans+=P*(M-id)+id*A[i]+wa[id];
    
  }
  
  cout<<ans<<endl;
}
#include<bits/stdc++.h>
using namespace std;

long long mincost(long long a,long long b,long long p,long long q,long long m){
  long long res=10000000000;
 
  for(long long i=a*b;i>=0;i--){//Aの個数
    if(a*i>=m)res=min(res,p*i);
    else res=min(res,p*i+q*((m-a*i+b-1)/b));
    }
  
  for(long long i=a*b;i>=0;i--){//Aの個数
    if(b*i>=m)res=min(res,q*i);
    else res=min(res,p*((m-b*i+a-1)/a)+q*i);
    }
  
  return res;
}

int main(){
  long long N,X;cin>>N>>X;
  vector<long long> A(N),P(N),B(N),Q(N);
  for(int i=0;i<N;i++)cin>>A[i]>>P[i]>>B[i]>>Q[i];
  
  long long l=0,r=1e10,m;
  
  while(r-l>1){
    //決め打ち二分探索
    m=(l+r)/2;
    long long copy=X;
    
    for(int i=0;i<N;i++){
      long long mc=mincost(A[i],B[i],P[i],Q[i],m);
      copy-=mc;
    }
    
    if(copy>=0)l=m;
    else r=m;
  }
  cout<<l<<endl;
  return 0;
}
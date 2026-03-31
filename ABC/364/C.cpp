#include<bits/stdc++.h>
using namespace std;

int main(){
  long long N,X,Y;cin>>N>>X>>Y;
  vector<long long> A(N),B(N);
  for(long long i=0;i<N;i++)cin>>A[i];
  for(long long i=0;i<N;i++)cin>>B[i];
  
  sort(A.begin(),A.end(),greater<long long>());sort(B.begin(),B.end(),greater<long long>());
  
  for(long long i=1;i<N;i++){
    A[i]=A[i]+A[i-1];
    B[i]=B[i]+B[i-1];
  }//累積和
  
  long long l=-1,r=N-1,m;
  long long ans1,ans2;
  
  while(r-l>1){
    m=(l+r)/2;
    
    if(A[m]>X)r=m;
    else l=m;
  }
  
  ans1=r;
  
  l=-1;r=N-1;
  
  while(r-l>1){
    m=(l+r)/2;
    
    if(B[m]>Y)r=m;
    else l=m;
  }
  ans2=r;
  
  cout<<min(ans1,ans2)+1<<endl;
}
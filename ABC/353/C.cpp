#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  long long ans=0;
  vector<long long> A(N+2);
  for(int i=0;i<N;i++)cin>>A[i];
  A[N]=-LLONG_MAX,A[N+1]=LLONG_MAX;
  sort(A.begin(),A.end());
  for(int i=1;i<=N;i++)ans+=(N-1)*A[i];
  
  long long cnt=0;
  
  for(int i=1;i<N;i++){
    int l=i,r=N+1,m;
    
    while(r-l>1){
      m=(r+l)/2;
      if(A[i]+A[m]<100'000'000)l=m;
      else r=m;
    }
    
    //cout<<N-l<<endl;
    cnt+=N-l;
    
    
  }
  
  
  ans-=100'000'000*cnt;
  
  cout<<ans<<endl;
}
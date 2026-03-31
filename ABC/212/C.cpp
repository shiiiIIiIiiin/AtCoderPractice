#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,M;cin>>N>>M;
  
  vector<int> A(N),B(M);
  
  for(int i=0;i<N;i++)cin>>A[i];
  for(int i=0;i<M;i++)cin>>B[i];
  
  sort(B.begin(),B.end());
  
  int ans=1000000000;
  
  for(int i=0;i<N;i++){
    int a=A[i];
    
    int l=0,r=M,m;
    
    while(r-l>1){
      m=(r+l)/2;
      
      if(B[m]<a)l=m;
      else r=m;
    }
    
    ans=min(abs(a-B[l]),min(abs(a-B[l+1]),ans));
    
    
  }
  
  cout<<ans<<endl;
}
#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,M;cin>>N>>M;
  vector<int> A(N),B(M);
  
  for(int i=0;i<N;i++)cin>>A[i];
  for(int i=0;i<M;i++)cin>>B[i];
  
  vector<int> c(N);
  int cnt=INT_MAX;
  for(int i=0;i<N;i++){
    if(cnt>A[i]){
      cnt=A[i];
    }
    
    c[i]=cnt;
  }
  
  /*
  for(int i=0;i<N;i++)cout<<c[i]<<" ";
  cout<<endl;
  */
  
  for(int i=0;i<M;i++){
    //M個のクエリに答える
    int l=-1,r=N,m;
    while(r-l>1){
      m=(l+r)/2;
      if(c[m]<=B[i])r=m;
      else l=m;
    }
    cout<<(r==N ? -1:r+1)<<endl;
  }
}
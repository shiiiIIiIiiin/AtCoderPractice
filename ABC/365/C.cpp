#include<bits/stdc++.h>
using namespace std;

int main(){
  long long N,M;cin>>N>>M;
  
  vector<long long> A(N);
  for(int i=0;i<N;i++)cin>>A[i];
  
  long long sum=0;
  for(int i=0;i<N;i++)sum+=A[i];
  if(sum<=M){
    cout<<"infinite"<<endl;
    return 0;
  }
  
  sort(A.begin(),A.end());
  
  long long l=0,r=M,m;
  
  while(r-l>1){
    m=(l+r)/2;
    long long s=0;
    for(int i=0;i<N;i++){
      if(A[i]>=m)s+=m;
      else s+=A[i];
    }
    
    if(s>M)r=m;
    else if(s<=M)l=m;
    
  }
  
  cout<<l<<endl;
  
}
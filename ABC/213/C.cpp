#include<bits/stdc++.h>
using namespace std;
int main(){
  int H,W,N;cin>>H>>W>>N;
  vector<int> A(N),B(N),ca(N),cb(N);
  
  for(int i=0;i<N;i++){
    cin>>A[i]>>B[i];
    ca[i]=A[i];
    cb[i]=B[i];
  }
  
  sort(ca.begin(),ca.end());
  sort(cb.begin(),cb.end());
  
  vector<int> a,b;
  a.push_back(ca[0]);
  b.push_back(cb[0]);
  for(int i=1;i<ca.size();i++)if(ca[i]!=ca[i-1])a.push_back(ca[i]);
  for(int i=1;i<cb.size();i++)if(cb[i]!=cb[i-1])b.push_back(cb[i]);
  
  for(int i=0;i<N;i++){
    int r=a.size(),l=-1,m;
    
    while(r-l>1){
      m=(r+l)/2;
      if(a[m]<A[i])l=m;
      else if(a[m]==A[i])break;
      else r=m;
    }
    
    cout<<m+1<<" ";
    
    r=b.size(),l=-1;
    
    while(r-l>1){
      m=(r+l)/2;
      if(b[m]<B[i])l=m;
      else if(b[m]==B[i])break;
      else r=m;
    }
    
    cout<<m+1<<endl;
    
  }
  
}
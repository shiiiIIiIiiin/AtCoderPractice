#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,Q;cin>>N;
  vector<int> A(N);
  for(int i=0;i<N;i++)cin>>A[i];
  sort(A.begin(),A.end());
  cin>>Q;
  
  
  for(int i=0;i<Q;i++){
    int l=0,r=N,m,x;cin>>x;
    
    //A[l]...必ずA[l]<xを満たす
    //A[r]...必ずA[r]>=xを満たす
    //求める値はl+1
    while(r-l>1){
      m=(r+l)/2;
      if(A[m]<x)l=m;
      else r=m;
    }
    cout<<(A[0]>=x ? 0 : l+1)<<endl;
  }
  return 0;
}
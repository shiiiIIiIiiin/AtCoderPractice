#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,L,R;cin>>N>>L>>R;
  vector<int> A(N);
  for(int i=0;i<N;i++)cin>>A[i];
  
  for(int i=1;i<=N;i++){
    if(A[i-1]<L)cout<<L<<" ";
    else if(L<=A[i-1]&&A[i-1]<=R)cout<<A[i-1]<<" ";
    else cout<<R<<" ";
  }
  
}
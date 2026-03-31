#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,K;cin>>N>>K;
  vector<int> A(N+K);
  for(int i=0;i<N;i++)cin>>A[i];
  
  for(int i=N-K;i<N;i++)cout<<A[i]<<" ";
  for(int i=0;i<N-K;i++)cout<<A[i]<<" ";
}
#include <bits/stdc++.h>
using namespace std;

int main() {
  int N,K,X;
  cin>>N>>K>>X;
  int A[N+1];
  for(int i=0;i<K;i++)cin>>A[i];
  A[K]=X;
  for(int i=K+1;i<N+1;i++)cin>>A[i];
  for(int i=0;i<N+1;i++)cout<<A[i]<<" ";
  cout<<endl;
}

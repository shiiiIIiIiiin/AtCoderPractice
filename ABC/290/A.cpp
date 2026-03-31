#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,M;cin>>N>>M;
  vector<int> A(N);
  for(int i=0;i<N;i++)cin>>A[i];
  
  long long ans=0;
  for(int i=0;i<M;i++){
    int b;cin>>b;
    ans+=A[b-1];
  }
  cout<<ans<<endl;
}
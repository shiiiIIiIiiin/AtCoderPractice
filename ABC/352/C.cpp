#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,i;
  cin>>N;
  vector<long long> A(N),B(N),C(N);
  for(i=0;i<N;i++)cin>>A[i]>>B[i];

  long long ans=0;
  for(i=0;i<N;i++){
    ans+=A[i];
    C[i]=B[i]-A[i];
  }

  sort(C.begin(),C.end());

  ans+=C.at(N-1);
  cout<<ans<<endl;

}
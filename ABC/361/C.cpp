#include <bits/stdc++.h>
using namespace std;

int main() {
  int N,K;
  cin>>N>>K;
  vector<long int>A(N);
  for(int i=0;i<N;i++)cin>>A[i];
  
  sort(A.begin(),A.end());
  
  long int min=1'000'000'000;
  
  for(int i=0;i<=K;i++){
    if(min>A[N-1-i]-A[K-i])min=A[N-1-i]-A[K-i];
  }
  
  cout<<min<<endl;
  
}

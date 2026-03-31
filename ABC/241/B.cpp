#include <bits/stdc++.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
using ll = long long;

int main() {
  int N,M;cin>>N>>M;
  vector<int> A(N),B(M);
  for(int i=0;i<N;i++)cin>>A[i];
  for(int j=0;j<M;j++)cin>>B[j];
  
  for(int i=0;i<M;i++){
    for(int j=0;j<N;j++){
      if(A[j]==B[i]){
        A[j]=-1;
        break;
      }
      
      if(j==N-1){
        cout<<"No";
        return 0;
      }
    }
  }
  
  cout<<"Yes";
}
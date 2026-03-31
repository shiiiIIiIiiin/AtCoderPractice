#include <bits/stdc++.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
using ll = long long;

int main() {
  int N;cin>>N;
  vector<int> A(N);
  for(int i=0;i<N;i++)cin>>A[i];
  
  //答えで二分探索...0<=K<=N/2
  int l=-1,r=N/2+1,m;
  
  while(r-l>1){
    m=(r+l)/2;
    bool can=true;
    
    for(int i=0;i<m;i++){
      if(A[i]*2>A[N-m+i])can=false;
    }
    
    if(can)l=m;
    else r=m;
  }
  
  cout<<l<<endl;
}
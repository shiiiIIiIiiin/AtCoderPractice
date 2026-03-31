#include <bits/stdc++.h>
using namespace std;

int main() {
  int N,M;cin>>N>>M;
  vector<int> A(M);
  vector<char> B(M);
  
  vector<bool> f(N+1,false);
  
  for(int i=0;i<M;i++){
    cin>>A[i]>>B[i];
    if(f[A[i]]||B[i]=='F')cout<<"No"<<endl;
    else cout<<"Yes"<<endl;
    
    if(B[i]=='M')f[A[i]]=true;
  }
  
  
}
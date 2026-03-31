#include<bits/stdc++.h>
#include<atcoder/all>
using namespace atcoder;
using namespace std;
using ll=long long;

int main(){
  int N,D;cin>>N>>D;
  vector<int> T(N),L(N);
  for(int i=0;i<N;i++)cin>>T[i]>>L[i];
  
  for(int i=1;i<=D;i++){
    int M=-1;
    for(int j=0;j<N;j++)M=max(M,T[j]*(L[j]+i));
    cout<<M<<endl;
    
  }
}
#include <bits/stdc++.h>
using namespace std;

int main(){
  int N,M;cin>>N>>M;
  vector<string> C(N),D(M);
  vector<int> P(M+1);
  for(int i=0;i<N;i++)cin>>C[i];
  for(int i=0;i<M;i++)cin>>D[i];
  cin>>P[M];
  for(int i=0;i<M;i++)cin>>P[i];
  
  
  long long ans=0;
  
  for(int i=0;i<N;i++){
    bool f=true;
    for(int j=0;j<M;j++)if(C[i]==D[j]){
      ans+=P[j];
      f=false;
    }
    if(f)ans+=P[M];
  }
  cout<<ans<<endl;
}
#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  vector<vector<int>> H(N+1,vector<int>(0));
  int A[N],W[N];
  for(int i=0;i<N;i++)cin>>A[i];
  for(int i=0;i<N;i++)cin>>W[i];
  
  for(int i=0;i<N;i++)H[A[i]].push_back(W[i]);
  
  for(int i=1;i<=N;i++)if(H[i].size()>=1)sort(H[i].begin(),H[i].end());
  
  long long ans=0;
  
  for(int i=1;i<=N;i++){
    if(!H[i].empty()){
      for(auto w:H[i])ans+=w;
      ans-=H[i][H[i].size()-1];
    }
  }
  
  cout<<ans<<endl;
  return 0;
}
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
  int N,M;cin>>N>>M;
  string S,ans;
  cin>>S;
  vector<int> C(N);
  for(int i=0;i<N;i++)cin>>C[i],C[i]--;
  vector<vector<int>> color(M);
  for(int i=0;i<N;i++)color[C[i]].push_back(i);
  
  for(int i=0;i<N;i++)ans+="@";
  
  for(int i=0;i<M;i++){
    for(int j=0;j<color[i].size();j++){
      ans[color[i][(j+1)%color[i].size()]]=S[color[i][j]];
    }
  }
  
  cout<<ans<<endl;
}
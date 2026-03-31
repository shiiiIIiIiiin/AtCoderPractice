#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main() {
  int N;cin>>N;
  vector<vector<int>> memo(37);
  vector<int> C(N+1);
  
  for(int i=1;i<=N;i++){
    int a;cin>>C[i];
    for(int j=0;j<C[i];j++){
      cin>>a;
      memo[a].push_back(i);
    }
  }
  
  int X;cin>>X;
  
  vector<int> ans;
  
  int m=INT_MAX;
  
  for(int i=0;i<memo[X].size();i++){
    if(m>C[memo[X][i]]){
      m=C[memo[X][i]];
      ans.clear();
    }
    
    if(C[memo[X][i]]==m)ans.push_back(memo[X][i]);
  }
  
  cout<<ans.size()<<endl;
  
  for(int i=0;i<ans.size();i++){
    cout<<ans[i]<<" ";
  }
}
#include <bits/stdc++.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
using ll = long long;

int main(){
  int K;cin>>K;
  vector<ll> ans;
  
  for(int i=1;i<(1<<10);i++){
    vector<int> s;
    
    for(int j=0;j<10;j++)if(i&(1<<j))s.push_back(j);
    
    sort(s.begin(),s.end());
    
    ll memo=0;
    for(int j=0;j<s.size();j++){
      memo*=10;
      memo+=s[s.size()-1-j];
    }
    
    if(memo!=0)ans.push_back(memo);
  }
  
  sort(ans.begin(),ans.end());
  
  cout<<ans[K-1];
}
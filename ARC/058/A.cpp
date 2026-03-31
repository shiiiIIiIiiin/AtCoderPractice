#include <bits/stdc++.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
using ll = long long;

int main(){
  int N,K;cin>>N>>K;
  set<int> D;
  for(int i=0;i<N;i++){
    int a;cin>>a;
    D.insert(a);
  }
  
  ll ans=N;
  
  while(true){
    string s=to_string(ans);
    for(int i=0;i<s.size();i++){
      if(D.count(int(s[i]-'0')))break;
      if(i+1==s.size()){
        cout<<s<<endl;
        return 0;
      }
    }
    ans++;
  }
}
#include <bits/stdc++.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
using ll = long long;

int main(){
  string s,ans="";
  cin>>s;
  
  for(int i=0;i<s[0]-'0';i++)ans+=s;
  cout<<ans;
}
#include <bits/stdc++.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
using ll = long long;

int main(){
  string s,t;cin>>s>>t;
  
  if(abs(s[0]-s[1])==abs(t[0]-t[1])||abs(s[0]-s[1])==5-abs(t[0]-t[1]))cout<<"Yes";
  else cout<<"No";
  
  
}
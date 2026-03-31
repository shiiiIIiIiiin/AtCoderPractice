#include<bits/stdc++.h>
using namespace std;
#define MOD 998244353

int main(){
  int S,T,X;cin>>S>>T>>X;
  if(S>T){
    T+=24;
    if(X<S)X+=24;
  }
  if(S<=X&&X<T)cout<<"Yes"<<endl;
  else cout<<"No"<<endl;
  
  return 0;
}
#include <bits/stdc++.h>
using namespace std;

bool kaibun(string s){
  for(int i=0;i<s.size();i++){
    if(s[i]!=s[s.size()-1-i])return false;
  }
  
  return true;
}

int main(){
  long long N;cin>>N;
  long long ans=-1;
  for(long long i=0;i*i*i<=N;i++){
    if(kaibun(to_string(i*i*i)))ans=i*i*i;
  }
  
  cout<<ans<<endl;
}
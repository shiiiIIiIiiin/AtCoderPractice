#include<bits/stdc++.h>
#include<atcoder/all>
using namespace atcoder;
using namespace std;

bool kaibun(string S){
  for(int i=0;i<S.size();i++){
    if(S[i]!=S[S.size()-1-i])return false;
  }
  return true;
}

int main(){
  string S,T;cin>>S;
  T=S;
  reverse(T.begin(),T.end());
  int N=S.size();
  int ans=0;
  
  for(int i=1;i<=N;i++){//何文字の回文
    bool flag=false;
    for(int j=0;j<=N-i;j++){
      for(int k=0;k<=N-i;k++){
       if(S.substr(j,i)==T.substr(k,i)&&kaibun(S.substr(j,i)))flag=true;
      }
    }
    
    if(flag)ans=i;
  }
  
  cout<<ans<<endl;
}
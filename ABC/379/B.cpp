#include<bits/stdc++.h>
#include<atcoder/all>
using namespace atcoder;
using namespace std;

int main(){
  int N,K;cin>>N>>K;
  string S;cin>>S;
  int ans=0,cnt=0;
  for(int i=0;i<N;i++){
    cnt++;
    if(S[i]=='X')cnt=0;
    if(cnt==K){
      ans++;
      cnt=0;
    }
    
  }
  
  cout<<ans<<endl;
}
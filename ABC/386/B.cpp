#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
  string S;cin>>S;
  
  int cnt=0,ans=0;
  while(cnt<S.size()){
    if(cnt<S.size()-1&&S[cnt]=='0'&&S[cnt+1]=='0'){
      ans++;
      cnt+=2;
    }
    else{
      cnt++;
      ans++;
    }
  }
  
  cout<<ans<<endl;
}
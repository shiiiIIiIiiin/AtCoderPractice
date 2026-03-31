#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,D;cin>>N>>D;
  vector<string> S(N);
  
  for(int i=0;i<N;i++){
    string t;cin>>t;
    S[i]=t;
  }
  
  bool ok[D];for(int i=0;i<D;i++)ok[i]=false;
  
  for(int i=0;i<D;i++){
    bool can=true;
    for(int j=0;j<N;j++){
     if(S[j][i]=='x')can=false;
    }
    if(can)ok[i]=true;
  }
  
  int ans=0,cnt=0;
  
  for(int i=0;i<D;i++){
    if(ok[i])cnt++;
    else{
      ans=max(ans,cnt);
      cnt=0;
    }
  }
  
  ans=max(ans,cnt);
  
  cout<<ans<<endl;
}
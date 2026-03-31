#include<bits/stdc++.h>
using namespace std;

int main(){
  string S;cin>>S;
  int ans=0;
  
  vector<int> pos(26);
  for(int i=0;i<26;i++){
    pos[S[i]-'A']=i;
  }
  
  for(int i=0;i<25;i++)ans+=abs(pos[i]-pos[i+1]);
  
  cout<<ans<<endl;
}
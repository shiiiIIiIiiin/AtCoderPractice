#include<bits/stdc++.h>
using namespace std;

int main(){
  vector<string> S(12);
  for(int i=0;i<12;i++)cin>>S[i];
  int ans=0;
  for(int i=0;i<12;i++){
    if(S[i].size()==i+1)ans++;
  }
  cout<<ans<<endl;
}
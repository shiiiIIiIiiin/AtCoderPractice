#include<bits/stdc++.h>
#include<atcoder/all>
using namespace atcoder;
using namespace std;

int main(){
  string S;cin>>S;
  vector<int> ans;
  
  for(int i=0;i<S.size();i++){
    int cnt=0;
    while(S[i]=='-'){
      cnt++;
      i++;
      if(S[i]=='|')break;
    }
    ans.push_back(cnt);
  }
  
  for(int i=1;i<ans.size();i++)cout<<ans[i]<<" ";
}
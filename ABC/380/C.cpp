#include<bits/stdc++.h>
#include<atcoder/all>
using namespace atcoder;
using namespace std;

int main(){
  int N,K;cin>>N>>K;
  string S;cin>>S;
  
  vector<string> memo;
  
  string t;
  t+=S[0];
  for(int i=1;i<S.size();i++){
    t+=S[i];
    if(S[i-1]=='1'&&S[i]=='0'){
      memo.push_back(t.substr(0,t.size()-1));
      if(i!=S.size()-1)t='0';
    }
  }
  memo.push_back(t);
  
  
  reverse(memo[K-1].begin(),memo[K-1].end());
  for(int i=0;i<memo.size();i++)cout<<memo[i];
}
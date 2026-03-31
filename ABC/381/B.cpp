#include<bits/stdc++.h>
#include<atcoder/all>
using namespace atcoder;
using namespace std;

int main(){
  string S;cin>>S;
  vector<bool> memo(26,false);
  bool ans=true;
  
  if(S.size()%2!=0){
    cout<<"No"<<endl;
    return 0;
  }
  
  for(int i=0;i<S.size();i+=2){
    if(memo[S[i]-'a'])ans=false;
    memo[S[i]-'a']=true;
    if(S[i]!=S[i+1])ans=false;
  }
  
  cout<<(ans?"Yes":"No")<<endl;
}
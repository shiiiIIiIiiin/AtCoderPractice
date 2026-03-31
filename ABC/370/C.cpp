#include<bits/stdc++.h>
using namespace std;

int main(){
  string S,T;cin>>S>>T;
  vector<int> p,q;

  for(int i=0;i<S.size();i++){
    if(int(S[i]-T[i])<0)p.push_back(i);//後で変える
    if(int(S[i]-T[i])>0)q.push_back(i);
  }

  vector<string> ans;


  for(int i=0;i<q.size();i++){
    S[q[i]]=T[q[i]];
    ans.push_back(S);
  }


  for(int i=p.size()-1;i>=0;i--){
    S[p[i]]=T[p[i]];
    ans.push_back(S);
  }


  cout<<ans.size()<<endl;
  for(int i=0;i<ans.size();i++)cout<<ans[i]<<endl;
  
  return 0;
}
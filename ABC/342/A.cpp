#include<bits/stdc++.h>
using namespace std;

int main(){
  string S;cin>>S;
  char c;
  
  if(S[0]==S[1])c=S[0];
  else if(S[0]==S[2])c=S[0];
  else c=S[1];
  
  for(int i=0;i<S.size();i++)if(S[i]!=c)cout<<i+1<<endl;
}
#include<bits/stdc++.h>
using namespace std;

int main(){
  string S;cin>>S;
  
  bool f=false;
  
  for(int i=0;i<3;i++){
    if(int(S[i]+1)%10!=int(S[i+1])%10)f=true;
  }
  
  if(S[0]==S[1]&&S[1]==S[2]&&S[2]==S[3])f=false;
  
  if(f)cout<<"Strong"<<endl;
  else cout<<"Weak"<<endl;
  
  return 0;
  
}
#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,M;cin>>N>>M;
  string S,T;cin>>S>>T;
  
  bool f1=true,f2=true;
  
  for(int i=0;i<N;i++){
    if(S[i]!=T[i])f1=false;
  }
  
  for(int i=0;i<N;i++){
    if(S[i]!=T[M-N+i])f2=false;
  }
  
  if(f1&&f2)cout<<0<<endl;
  else if(f1)cout<<1<<endl;
  else if(f2)cout<<2<<endl;
  else cout<<3<<endl;
}
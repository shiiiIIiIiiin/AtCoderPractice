#include<bits/stdc++.h>
using namespace std;

int main(){
  string S,T;cin>>S>>T;
  
  if(S==T){
    cout<<0<<endl;
  }
  else{
    int m=min(S.size(),T.size());
    for(int i=0;i<m;i++){
      if(S[i]!=T[i]){
        cout<<i+1<<endl;
        return 0;
      }
      if(i==m-1&&S.size()!=T.size())cout<<i+2<<endl;
      
    }
  }
  
}
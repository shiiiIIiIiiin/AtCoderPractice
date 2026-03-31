#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,D;cin>>N>>D;
  string S;cin>>S;
  
  for(int i=0;i<D;i++){
    for(int j=S.size()-1;j>=0;j--){
      if(S[j]=='@'){
        S[j]='.';
        break;
      }
      
    }
  }
  
  cout<<S<<endl;
}
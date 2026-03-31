#include <bits/stdc++.h>
using namespace std;

int main() {
  string S,T;
  cin>>S>>T;
  
  for(int w=1;w<S.size();w++){
    for(int c=0;c<w;c++){
      string ans="";
      for(int i=c;i<S.size();i+=w){
        ans+=S[i];
      }
      
      if(ans==T){
        cout<<"Yes"<<endl;
        return 0;
      }
    }
  }
  cout<<"No"<<endl;
}
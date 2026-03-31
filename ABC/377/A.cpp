#include <bits/stdc++.h>
using namespace std;

int main(){
  vector<bool> f(3);
  string S;cin>>S;
  for(int i=0;i<3;i++){
    if(int(S[i]-'A')>=3)continue;
    f[int(S[i]-'A')]=true;
  }
  
  for(int i=0;i<3;i++){
    if(!f[i]){
      cout<<"No"<<endl;
      return 0;
    }
  }
  
  cout<<"Yes"<<endl;
}
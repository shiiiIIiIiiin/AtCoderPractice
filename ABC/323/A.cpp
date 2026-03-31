#include<bits/stdc++.h>
using namespace std;

int main(){
  string S;
  cin>>S;
  bool ok=true;
  for(int i=1;i<16;i+=2){
    if(S[i]=='1')ok=false;
  }
  cout<<(ok ? "Yes":"No")<<endl;
}
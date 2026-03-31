#include<bits/stdc++.h>
using namespace std;

int main(){
  string S;
  cin>>S;
  
  string t;
  int cnt=S.size()-1;
  while(S[cnt]!='.'&&cnt>=0){
    t+=S[cnt];
    cnt--;
  }
  for(int i=0;i<t.size();i++){
    cout<<t[t.size()-i-1];
  }
  cout<<endl;
}
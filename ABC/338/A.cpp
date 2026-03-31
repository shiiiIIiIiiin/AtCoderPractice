#include<bits/stdc++.h>
using namespace std;
int main(){
  string S;
  cin>>S;
  
  bool ans=true;
  
  if('A'>S.at(0)||S.at(0)>'Z')ans=false;
  
  for(int i=1;i<S.size();i++){
    if('a'>S.at(i)||S.at(i)>'z')ans=false;
  }
  cout<<(ans?"Yes":"No")<<endl;
}
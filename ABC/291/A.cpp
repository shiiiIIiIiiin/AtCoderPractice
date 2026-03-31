#include<bits/stdc++.h>
using namespace std;

int main(){
  string S;
  cin>>S;
  
  for(int i=0;i<S.size();i++){
    if(0<=S[i]-'A'&&S[i]-'A'<=26)cout<<i+1<<endl;
  }
}
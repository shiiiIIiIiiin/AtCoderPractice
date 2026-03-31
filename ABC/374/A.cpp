#include<bits/stdc++.h>
using namespace std;

int main(){
  string S;cin>>S;
  
  int k=S.size()-1;
  
  if(S[k]=='n'&&S[k-1]=='a'&&S[k-2]=='s')cout<<"Yes"<<endl;
  else cout<<"No"<<endl;
}
#include<bits/stdc++.h>
#include<atcoder/all>
using namespace atcoder;
using namespace std;

int main(){
  int N;cin>>N;
  string S;cin>>S;
  string T="";
  for(int i=0;i<N/2;i++)T+='1';
  T+="/";
  for(int i=0;i<N/2;i++)T+='2';
  
  cout<<(S==T ? "Yes":"No")<<endl;
  
}
#include<bits/stdc++.h>
#include<atcoder/all>
using namespace atcoder;
using namespace std;

int main(){
  string S;cin>>S;
  for(int i=1;i<=3;i++)cout<<S[i%3];
  cout<<" ";
  for(int i=2;i<=4;i++)cout<<S[i%3];
}
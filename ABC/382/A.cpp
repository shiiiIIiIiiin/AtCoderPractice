#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,D;cin>>N>>D;
  string S;cin>>S;
  int cnt=0;
  for(int i=0;i<S.size();i++)if(S[i]=='.')cnt++;
  cout<<cnt+D<<endl;
}
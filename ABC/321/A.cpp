#include<bits/stdc++.h>
using namespace std;

int main(){
  bool ans=true;
  string S;cin>>S;
  int N=S.size();
  for(int i=0;i<N-1;i++)if(int(S[i]-'0')<=int(S[i+1]-'0'))ans=false;
  
  cout<<(ans ? "Yes":"No")<<endl;
}
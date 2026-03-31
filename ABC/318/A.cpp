#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
  int N,M,P;cin>>N>>M>>P;
  int ans=0;
  for(int i=M;i<=N;i+=P){
    ans++;
  }
  cout<<ans<<endl;
}
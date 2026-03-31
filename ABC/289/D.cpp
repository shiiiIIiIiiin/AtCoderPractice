#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  vector<int> A(N);
  for(int i=0;i<N;i++)cin>>A[i];
  int M;cin>>M;
  set<int> s;
  for(int i=0;i<M;i++){
    int b;cin>>b;
    s.insert(b);
  }
  int X;cin>>X;
  
  vector<bool> dp(X+1,false);
  dp[0]=true;
  
  for(int pos=0;pos<=X;pos++){
    if(!dp[pos])continue;
    for(int i=0;i<N;i++) if(pos+A[i]<=X&&!s.count(pos+A[i]))dp[pos+A[i]]=true;
  }
  
  cout<<(dp[X] ? "Yes":"No")<<endl;
  
}
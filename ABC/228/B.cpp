#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,X;cin>>N>>X;
  vector<int> A(N+1);
  for(int i=1;i<=N;i++)cin>>A[i];
  
  vector<bool> visited(N+1,false);
  int cnt=X,ans=0;
  
  while(true){
    visited[cnt]=true;
    ans++;
    if(visited[A[cnt]])break;
    cnt=A[cnt];
  }
  
  cout<<ans<<endl;
}
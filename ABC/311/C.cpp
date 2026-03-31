#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  vector<int> A(N+1);
  for(int i=1;i<=N;i++)cin>>A[i];
  vector<bool> visited(N+1,false);
  
  int pos=1;
  vector<int> ans;
  int cnt=0;
  
  
  while(true){
    visited[pos]=true;
    
    if(visited[A[pos]])break;//閉路検出
      
      pos=A[pos];
  }
  
  vector<bool> visited2(N+1,false);
  
  while(true){
    visited2[pos]=true;
    ans.push_back(pos);
    cnt++;
    if(visited2[A[pos]])break;
    pos=A[pos];
  }
  
  cout<<cnt<<endl;
  for(auto x:ans)cout<<x<<" ";
  
}
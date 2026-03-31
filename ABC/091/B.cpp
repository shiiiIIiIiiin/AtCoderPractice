#include<bits/stdc++.h>
using namespace std;
int main(){
  int N,M,i,j;
  cin>>N;
  vector<string> s(N);
  for(i=0;i<N;i++)cin>>s.at(i);
  cin>>M;
  vector<string> t(M);
  for(i=0;i<M;i++)cin>>t.at(i);
  
  int ans=0,memo=0;
  for(i=0;i<N;i++){
   for(j=0;j<N;j++){
   if(s.at(i)==s.at(j))memo++;
   }
   for(j=0;j<M;j++){
     if(s.at(i)==t.at(j))memo--;
   }
    ans=max(ans,memo);
    memo=0;
  }
  cout<<ans<<endl;
}
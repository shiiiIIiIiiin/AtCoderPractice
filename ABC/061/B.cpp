#include<bits/stdc++.h>
using namespace std;
int main(){
  int N,M,i;
  cin>>N>>M;
  vector<int> a(M),b(M),c(N);
  for(i=0;i<N;i++)c.at(i)=0;
  for(i=0;i<M;i++)cin>>a.at(i)>>b.at(i);
  for(i=0;i<M;i++){
    c.at(a.at(i)-1)++;c.at(b.at(i)-1)++;
  }
  for(i=0;i<N;i++)cout<<c.at(i)<<endl;
}
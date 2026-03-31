#include <bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  map<long long,long long> m;
  
  for(int i=0;i<N;i++){
    int s,c;cin>>s>>c;
    m[s]=c;
  }
  
  for(auto x:m){
    long long id=x.first,cnt=x.second;
    m[id]-=cnt-cnt%2;
    m[2*id]+=cnt/2;
  }
  
  long long ans=0;
  
  for(auto x:m)ans+=x.second;
  
  cout<<ans<<endl;
}
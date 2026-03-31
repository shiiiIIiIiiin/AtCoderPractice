#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  vector<long long> T(N);
  for(int i=0;i<N;i++)cin>>T[i];
  
  sort(T.begin(),T.end());
  T.erase(unique(T.begin(),T.end()),T.end());
  
  long long ans=T[0];
  
  for(int i=0;i<T.size();i++){
    ans=lcm(ans,T[i]);
  }
  cout<<ans<<endl;
}
#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;cin>>N;
  int ans=0;
  vector<int> T(N),V(N);
  for(int i=0;i<N;i++)cin>>T[i]>>V[i];
  
  ans+=V[0];
  
  for(int i=1;i<N;i++){
    ans=max(0,ans-(T[i]-T[i-1]));
    ans+=V[i];
  }
  
  cout<<ans<<endl;
}
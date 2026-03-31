#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  vector<int> q(N),r(N);
  for(int i=0;i<N;i++)cin>>q[i]>>r[i];
  int Q;cin>>Q;
  
  for(int i=0;i<Q;i++){
    int t,d;cin>>t>>d;
    t--;
    int ans=r[t]-d%q[t]+d;
    
    if(d%q[t]>r[t])ans+=q[t];
    cout<<ans<<endl;
  }
}
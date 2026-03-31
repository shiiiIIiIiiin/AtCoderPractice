#include <bits/stdc++.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
using ll = long long;

int main(){
  ll N,M;cin>>N>>M;
  vector<ll> A(N+1);
  ll ans=0;
  for(int i=1;i<=N;i++)cin>>A[i];
  A[0]=0;
  
  //for(int i=0;i<N;i++)if(A[i]%M==0)ans++;
  
  for(int i=1;i<=N;i++){
    A[i]+=A[i-1];
    A[i]%=M;
  }
  
  map<ll,ll> cnt;
  
  for(int i=0;i<=N;i++)cnt[A[i]]++;
  
  for(auto x:cnt)if(x.second!=0)ans+=x.second*(x.second-1)/2;
  
  cout<<ans<<endl;
}
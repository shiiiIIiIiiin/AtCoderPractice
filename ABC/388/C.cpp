#include<bits/stdc++.h>
#include<atcoder/all>
using namespace atcoder;
using namespace std;
using ll=long long;

int main(){
  int N;cin>>N;
  vector<int> A(N);
  for(int i=0;i<N;i++)cin>>A[i];
  sort(A.begin(),A.end());
  
  ll ans=0;
  
  for(int i=0;i<N-1;i++){//上の餅がiの時
    int l=i,r=N,m;
    
    while(r-l>1){
      m=(r+l)/2;
      if(2*A[i]<=A[m])r=m;
      else l=m;
    }
    
    //cout<<N-r<<endl;
    ans+=N-r;
  }
  
  cout<<ans<<endl;
}
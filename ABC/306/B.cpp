#include<bits/stdc++.h>
using namespace std;

int main(){
  unsigned long long ans=0;
  vector<long long> A(64);
  for(int i=0;i<64;i++)cin>>A[i];
  long long scale=1;
  for(int i=0;i<64;i++){
    ans+=scale*A[i];
    scale*=2;
  }
  cout<<ans<<endl;
}
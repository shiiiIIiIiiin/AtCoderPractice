#include<bits/stdc++.h>
#include<atcoder/all>
using namespace atcoder;
using namespace std;

int main(){
  int N;cin>>N;
  long long ans=0;
  for(int i=0;i<N;i++){
    long long A,B;cin>>A>>B;
    ans+=(B-A+1)*(A+B)/2;
  }
  cout<<ans<<endl;
}
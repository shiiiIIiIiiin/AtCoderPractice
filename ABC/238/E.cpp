#include<bits/stdc++.h>
#include<atcoder/all>
using namespace atcoder;
using namespace std;

int main(){
  int N,Q;cin>>N>>Q;
  dsu uf(N+1);
  
  for(int i=0;i<Q;i++){
    int l,r;cin>>l>>r;
    uf.merge(l-1,r);
  }
  
  cout<<(uf.same(0,N) ? "Yes":"No")<<endl;
}
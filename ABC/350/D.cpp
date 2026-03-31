#include<bits/stdc++.h>
#include<atcoder/all>
using namespace atcoder;
using namespace std;

int main(){
  int N,M;cin>>N>>M;
  dsu uf(N);
  
  vector<int> a(M),b(M);
  for(int i=0;i<M;i++){
    cin>>a[i]>>b[i];
    a[i]--,b[i]--;
    uf.merge(a[i],b[i]);
  }
  
  long long ans=0;
  set<int> s;
  for(int i=0;i<N;i++){
    int id=uf.leader(i);
    if(!s.count(id)){
      s.insert(id);
      ans+=(long long)(uf.size(i))*(long long)(uf.size(i)-1)/2;
    }
  }
  
  ans-=M;//もともとあった辺を抜く
  
  cout<<ans<<endl;
}
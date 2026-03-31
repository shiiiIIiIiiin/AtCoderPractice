#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,M;cin>>N>>M;
  vector<set<int>> m(N+1);
  
  for(int i=0;i<M;i++){
    vector<int> a(N);
    for(int j=0;j<N;j++)cin>>a[j];
    
    m[a[0]].insert(a[1]);
    for(int j=1;j<N-1;j++){
      m[a[j]].insert(a[j-1]);
      m[a[j]].insert(a[j+1]);
    }
    m[a[N-1]].insert(a[N-2]);
  }
  
  int ans=0;
  
  for(int i=1;i<=N;i++){//人iと不仲な人を挙げる
    vector<bool> g(N+1,false);
    for(auto x:m[i])g[x]=true;
    
    for(int j=i+1;j<=N;j++){
      if(!g[j])ans++;
    }
  }
  
  cout<<ans<<endl;
}
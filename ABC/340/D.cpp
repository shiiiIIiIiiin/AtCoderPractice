#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;cin>>N;
  vector<vector<pair<int,int>>> G(N+1);
  
  
  
  for(int i=1;i<=N-1;i++){
    int a,b,x;cin>>a>>b>>x;
    G[i].push_back(pair(i+1,a));
    G[i].push_back(pair(x,b));
    
  }
  
  //ダイクストラ法
  
  priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> Q;
  long long cur[N+1];
  bool kakutei[N+1];
  for(int i=0;i<N+1;i++){
    cur[i]=200'000'000'000'000'000;
    kakutei[i]=false;
  }
  
  cur[1]=0;
  Q.push(pair(cur[1],1));
  
  while(!Q.empty()){
    //次に確定させるべき頂点を決める
    int pos=Q.top().second;Q.pop();
    //持ってきた頂点が確定済みのものだった場合
    if(kakutei[pos])continue;
    
    kakutei[pos]=true;
    for(int i=0;i<G[pos].size();i++){
      int nex=G[pos][i].first;
      long long cost=G[pos][i].second;
      
      if(cur[nex]>cur[pos]+cost){
        cur[nex]=cur[pos]+cost;
        Q.push(pair(cur[nex],nex));
      }
      
      
    }
    
  }
  
  cout<<cur[N]<<endl;
  
}
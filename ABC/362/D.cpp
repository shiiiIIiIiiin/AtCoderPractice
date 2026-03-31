#include <bits/stdc++.h>
using namespace std;

typedef struct graph{
  long long cost;
  vector<pair<long long,long long>> TO;//向かえる先,道のコスト
  
}graph;

int main(){
  long long N,M,i;
  cin>>N>>M;
  long long A[N+1],U[M+1],V[M+1],B[M+1];
  for(i=1;i<=N;i++)cin>>A[i];
  vector<graph> G(N+1);
  
  for(i=1;i<=M;i++)cin>>U[i]>>V[i]>>B[i];
  
  
  for(i=1;i<=N;i++)G[i].cost=A[i];
  
  for(i=1;i<=M;i++){
    G[U[i]].TO.push_back(pair(V[i],B[i]+G[U[i]].cost));
    G[V[i]].TO.push_back(pair(U[i],B[i]+G[V[i]].cost));
  }
  //ここまで入力とグラフ作り
  
  vector<bool> kakutei(N+1,false);
  vector<long long> cur(N+1,4'000'000'000'000'000);
  
  cur[1]=0;
  
  priority_queue<pair<long long,long long>,vector<pair<long long,long long>>,greater<pair<long long,long long>>> Q;
  
  Q.push(make_pair(cur[1],1));
  
  while(!Q.empty()){
    long long pos=Q.top().second;Q.pop();
    
    if(kakutei[pos])continue;
    
    kakutei[pos]=true;
    for(i=0;i<G[pos].TO.size();i++){
      long long nex=G[pos].TO.at(i).first;
      long long COST=G[pos].TO.at(i).second;
      
      if(cur[nex]>cur[pos]+COST){
        cur[nex]=cur[pos]+COST;
        Q.push(make_pair(cur[nex],nex));
      }
    }
  }
  
  for(i=2;i<N+1;i++)cout<<cur[i]+A[i]<<" ";
  cout<<endl;
  
}
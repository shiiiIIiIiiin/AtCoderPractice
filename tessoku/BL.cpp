#include <bits/stdc++.h>
using namespace std;

int main() {
  int N,M;
  cin>>N>>M;
  int A[M],B[M],C[M];
  vector<vector<pair<int,int>>> G(N+1);
  for(int i=0;i<M;i++){
    cin>>A[i]>>B[i]>>C[i];
    G[A[i]].push_back(pair(B[i],C[i]));
    G[B[i]].push_back(pair(A[i],C[i]));
  }
  
  queue<int> Q;
  int dist[N+1];
  for(int i=0;i<=N;i++)dist[i]=1000000000;
  
  Q.push(1);
  dist[1]=0;
  
  while(!Q.empty()){
    int pos=Q.front();Q.pop();
    for(int i=0;i<G[pos].size();i++){
      int to=G[pos][i].first,D=G[pos][i].second;
      if(dist[to]>dist[pos]+D){
        dist[to]=dist[pos]+D;
        Q.push(to);
      }
    }
  }
  
  for(int i=1;i<=N;i++){
    cout<<(dist[i]==1000000000 ? -1:dist[i])<<endl;
  }
}

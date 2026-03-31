#include<bits/stdc++.h>
using namespace std;

void dfs(int pre,int pos,vector<vector<int>> &G,vector<bool> &visited,int cnt[]){
  visited[pos]=true;
  cnt[pos]=cnt[pre]+1;
  
  for(int i=0;i<G[pos].size();i++){
    int nex=G[pos][i];
    if(visited[nex])continue;
    dfs(pos,nex,G,visited,cnt);
  }
  
  return;
}

int main(){
  int N;
  cin>>N;
  //道を全探索するのは無理
  //木の直径に１を足す
  
  vector<vector<int>> G(N+1);
  
  for(int i=0;i<N-1;i++){
    int a,b;cin>>a>>b;
    
    G[a].push_back(b);
    G[b].push_back(a);
  }
  G[0].push_back(1);
  
   int cnt[N+1]={0};
   cnt[0]=-1;
  vector<bool> visited(N+1,false);
  
  dfs(0,1,G,visited,cnt);
  
  int Max=0;
  
  for(int i=1;i<=N;i++)if(cnt[Max]<cnt[i])Max=i;
  
  //ここまで頂点1から一番遠い点がMaxに記録された
  
  //ここから第二弾まずはリセットする
  for(int i=0;i<=N;i++){
    visited[i]=false;
    cnt[i]=0;
  }
  
  cnt[0]=-1;
  
  G[0].pop_back();
  G[0].push_back(Max);
  
  dfs(0,Max,G,visited,cnt);
  
  int ans=0;
  
  for(int i=1;i<=N;i++)if(cnt[ans]<cnt[i])ans=i;
  
  cout<<cnt[ans]+1<<endl;
  
}
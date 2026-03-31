#include<bits/stdc++.h>
using namespace std;

int N,X,Y;
int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
vector<int> ans;

/*
bool ingrid(int x,int y){
  return (0<=x&&x<H&&0<=y&&y<W);
}
*/

bool dfs(vector<vector<int>> &G,int &pos,int &pre){
  
  for(int i=0;i<G[pos].size();i++){
    int nex=G[pos][i];
    if(nex==pre)continue;
    
    if(nex==Y){
      ans.push_back(nex);
      ans.push_back(pos);
      return true;
    }
    
    if(dfs(G,nex,pos)){
      ans.push_back(pos);
      return true;
    }
  }
  
  return false;
}

int main(){
  cin>>N>>X>>Y;
  vector<vector<int>> G(N+1);
  for(int i=0;i<N-1;i++){
    int u,v;cin>>u>>v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  
  //vector<bool> visited(N+1,false);
  int memo=-1;
  dfs(G,X,memo);
  reverse(ans.begin(),ans.end());
  
  for(int i=0;i<ans.size();i++)cout<<ans[i]<<" ";
  return 0;
}
#include <bits/stdc++.h>
using namespace std;

int H,W,K;
int dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};

bool hantei(vector<string> &S,int x,int y){
  return (0<=x&&x<H&&0<=y&&y<W&&S[x][y]=='.');
}

void dfs(vector<string> &S,vector<vector<bool>> &visited,int posx,int posy,long long &ans,int K){
  
  if(K==0){
    ans++;
    return;
  }
  
  visited[posx][posy]=true;
  
  for(int i=0;i<4;i++){
    int nx=posx+dx[i],ny=posy+dy[i];
    
    if(!hantei(S,nx,ny))continue;
    if(visited[nx][ny])continue;
    
    dfs(S,visited,nx,ny,ans,K-1);
    
  }
  
  visited[posx][posy]=false;
  
  return;
}

int main() {
  cin>>H>>W>>K;
  vector<string> S(H);
  for(int i=0;i<H;i++)cin>>S[i];
  
  long long ans=0;
  
  vector<vector<bool>> visited(H,vector<bool>(W,false));
  
  for(int i=0;i<H;i++)for(int j=0;j<W;j++){
    //vector<vector<bool>> visited(H,vector<bool>(W,false));
    if(S[i][j]=='.')dfs(S,visited,i,j,ans,K);
  }
  
  
  cout<<ans<<endl;
}
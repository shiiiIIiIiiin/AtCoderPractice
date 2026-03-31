#include <bits/stdc++.h>
using namespace std;

int dx[]={1,0,-1,0},dy[]={0,1,0,-1};

int main() {
  int H,W,D;cin>>H>>W>>D;
  vector<string> S(H);
  for(int i=0;i<H;i++)cin>>S[i];
  
  vector<vector<bool>> visited(H,vector<bool>(W,false));
  queue<tuple<int,int,int>> q;
  int ans=0;
  
  for(int i=0;i<H;i++)for(int j=0;j<W;j++){
    if(S[i][j]=='#')visited[i][j]=true;
    if(S[i][j]=='H'){
      visited[i][j]=true;
      q.push({i,j,0});
      ans++;
    }
  }
  
  
  while(!q.empty()){
    auto [x,y,d]=q.front();q.pop();
    
    for(int i=0;i<4;i++){
      int nx=x+dx[i],ny=y+dy[i];
      if(nx<0||H<=nx||ny<0||W<=ny)continue;
      if(visited[nx][ny]||d>=D)continue;
      
      visited[nx][ny]=true;
      q.push({nx,ny,d+1});
      ans++;
    }
  }
  
  cout<<ans<<endl;
}
#include<bits/stdc++.h>
using namespace std;

int H,W;
int dx[]={1,0,-1,0},dy[]={0,1,0,-1};

bool ingrid(int x,int y){
  return 0<=x&&x<H&&0<=y&&y<W;
}

int main(){
  cin>>H>>W;
  vector<string> A(H);
  for(int i=0;i<H;i++)cin>>A[i];
  
  queue<vector<int>> q;
  
  for(int i=0;i<H;i++)for(int j=0;j<W;j++)if(A[i][j]=='#')q.push({i,j,0});
  int ans=0;
  
  while(!q.empty()){
    vector<int> a=q.front();q.pop();
    for(int i=0;i<4;i++){
      int nx=a[0]+dx[i],ny=a[1]+dy[i];
      if(ingrid(nx,ny)&&A[nx][ny]=='.'){
        q.push({nx,ny,a[2]+1});
        ans=max(ans,a[2]+1);
        A[nx][ny]='#';
      }
    }
    
  }
  
  cout<<ans<<endl;
  
}
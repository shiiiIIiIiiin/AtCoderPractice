#include<bits/stdc++.h>
using namespace std;
using ll=long long;

string muki="UDLR";
int dx[]={-1,1,0,0},dy[]={0,0,-1,1};

int main(){
  int H,W,X,Y;cin>>H>>W>>X>>Y;
  X--;
  Y--;
  vector<string> S(H);
  vector<vector<bool>> visited(H,vector<bool>(W,false));
  for(int i=0;i<H;i++)cin>>S[i];
  string T;cin>>T;
  
  int ans=0;
  
  for(int i=0;i<T.size();i++){
    for(int j=0;j<4;j++){
      if(muki[j]!=T[i])continue;
      int nx=X+dx[j],ny=Y+dy[j];
      
      if(nx<0||H<=nx||ny<0||W<=ny||S[nx][ny]=='#')continue;
      
      if(S[nx][ny]=='@'&&!visited[nx][ny])ans++;
      X=nx;
      Y=ny;
      visited[nx][ny]=true;
      
    }
  }
  
  cout<<X+1<<" "<<Y+1<<" "<<ans<<endl;
}

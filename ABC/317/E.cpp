#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int H,W;
string muki=">^<v";//解説に書いてあった同じ処理を何回も書かないための工夫
ll dx[]={0,-1,0,1},dy[]={1,0,-1,0};

int main(){
  //入力
  cin>>H>>W;
  vector<string> G(H);
  for(int i=0;i<H;i++)cin>>G[i];
  
  
  
  
  //マスを加工する
  //視線が入っているマスは_に変える　視線は視線が通ったマスを通ることができることに注意した
  
  for(int h=0;h<H;h++)for(int w=0;w<W;w++){
    for(int d=0;d<4;d++){
      if(G[h][w]!=muki[d])continue;
      
      int px=h,py=w;
      px+=dx[d];
      py+=dy[d];
      
      while(true){
        if(px<0||px>=H||py<0||py>=W||(G[px][py]!='.'&&G[px][py]!='_'))break;//人か壁にぶつかったらやめる
        G[px][py]='_';//視線が入っていて壁ではないマスは_にする。ただし、視線が通ることはできる
        px+=dx[d];
        py+=dy[d];//向いてる方向に１マス進む
      }
      
    }
  }
  
  
  
  
  int sx,sy,gx,gy;//スタートとゴールの座標を入れる
  
  //視線が入ったマスと人がいるマスを壁に変える
  for(int i=0;i<H;i++)for(int j=0;j<W;j++){
    if(G[i][j]=='_')G[i][j]='#';//視線が入っているマスは通れないことにする
    
    for(int k=0;k<4;k++)if(G[i][j]==muki[k])G[i][j]='#';//人がいるマスを壁に変える
    
    if(G[i][j]=='S'){//ついでにスタートとゴールの座標を保持しておく
      sx=i;
      sy=j;
    }
    if(G[i][j]=='G'){
      gx=i;
      gy=j;
    }
  }
  
  /*デバッグ用
  for(int i=0;i<H;i++){
    for(int j=0;j<W;j++)cout<<G[i][j]<<" ";
    cout<<endl;
  }
  */
  
  
  
  
  
  
  //bfsをする（ここが間違ってそう）
  queue<tuple<ll,ll,ll>> q;
  q.push({0,sx,sy});
  vector<vector<bool>> visited(H,vector<bool>(W,false));
  visited[sx][sy]=true;
  
  while(!q.empty()){
    auto [c,posx,posy]=q.front();q.pop();
    
    for(int i=0;i<4;i++){
      int nx=posx+dx[i],ny=posy+dy[i];
      if(nx<0||nx>=H||ny<0||ny>=W||visited[nx][ny])continue;
      
      if(G[nx][ny]=='#')continue;
      
      
      if(G[nx][ny]=='G'){
        cout<<c+1<<endl;//ゴールだったら何回進んだかを出力する
        return 0;
      }
      
      visited[nx][ny]=true;
      q.push({c+1,nx,ny});
      
      
    }
    
  }
  
  
  cout<<-1<<endl;//ゴールまでいけなかったら-1を出力する
  
}
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int H,W;
int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
string t="snuke";

bool dfs(int posx,int posy,vector<string> &S,int poschar,vector<vector<bool>> &visited){
    visited[posx][posy]=true;

    if(posx==H-1&&posy==W-1)return true;

    for(int i=0;i<4;i++){
        int nx=posx+dx[i],ny=posy+dy[i];
        if(nx<0||H<=nx||ny<0||W<=ny)continue;//配列の外だったらダメ
        if(S[nx][ny]!=t[(poschar+1)%5])continue;//文字が違ったらダメ
        if(visited[nx][ny])continue;//もう来た事あったら探索しなくていい

        if(dfs(nx,ny,S,(poschar+1)%5,visited))return true;//こっちの方向に行けばゴールがあるなら進む
    }
    //visited[posx][posy]=false;
    
    return false;//どっちの方向に行ってもゴールに行けない場合はfalseを返す
}

int main(){
    cin>>H>>W;
    vector<string> S(H);
    for(int i=0;i<H;i++)cin>>S[i];
    vector<vector<bool>> visited(H,vector<bool>(W,false));
    cout<<(dfs(0,0,S,0,visited) ? "Yes":"No")<<endl;

    return 0;
}
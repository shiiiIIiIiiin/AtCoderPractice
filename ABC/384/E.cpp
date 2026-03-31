#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int H,W,X,P,Q;
int dx[]={1,0,-1,0},dy[]={0,1,0,-1};

int main(){
    cin>>H>>W>>X>>P>>Q;
    
    P--,Q--;
    vector<vector<ll>> S(H,vector<ll>(W));
    for(int i=0;i<H;i++)for(int j=0;j<W;j++)cin>>S[i][j];

    priority_queue<tuple<ll,ll,ll>,vector<tuple<ll,ll,ll>>,greater<tuple<ll,ll,ll>>> pq;//強さ、ｘ,ｙ座標を保持する
    long long ans=S[P][Q];
    vector<vector<bool>> visited(H,vector<bool>(W,false));
    visited[P][Q]=true;

    for(int i=0;i<4;i++){
        int x=P+dx[i],y=Q+dy[i];
        if(x<0||H<=x||y<0||W<=y)continue;
        pq.push({S[x][y],x,y});
        visited[x][y]=true;
    }
    

    
    while(!pq.empty()){
      
            auto [power,x,y]=pq.top();pq.pop();
            if((double)(ans)/X<=power)break;
            
            ans+=power;
            

        for(int i=0;i<4;i++){
            int nx=x+dx[i],ny=y+dy[i];
            if(nx<0||H<=nx||ny<0||W<=ny)continue;
            if(visited[nx][ny])continue;
            pq.push({S[nx][ny],nx,ny});
            visited[nx][ny]=true;
        }
    }
    
    cout<<ans<<endl;
}
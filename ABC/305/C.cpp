#include <bits/stdc++.h>
using namespace std;

int H,W;
int dx[]={1,0,-1,0},dy[]={0,1,0,-1};

bool check(vector<string> &S,int x,int y){
  int cnt=0;
  
  for(int i=0;i<4;i++){
    if(!(0<=x+dx[i]&&x+dx[i]<H&&0<=y+dy[i]&&y+dy[i]<W))continue;
    if(S[x+dx[i]][y+dy[i]]=='#')cnt++;
  }
  
  if(cnt>=2)return true;
  else return false;
}

int main() {
   cin>>H>>W;
   vector<string> S(H);
   for(int i=0;i<H;i++)cin>>S[i];
   
   for(int i=0;i<H;i++)for(int j=0;j<W;j++){
     if(check(S,i,j)&&S[i][j]=='.'){
       cout<<i+1<<" "<<j+1<<endl;
       return 0;
     }
   }
   
   
}
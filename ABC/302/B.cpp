#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int dx[]={1,1,0,-1,-1,-1,0,1},dy[]={0,1,1,1,0,-1,-1,-1};
string s="snuke";

int main(){
  int H,W;cin>>H>>W;
  vector<string> S(H);
  for(int i=0;i<H;i++)cin>>S[i];
  
  for(int i=0;i<H;i++){
    for(int j=0;j<W;j++){
      if(S[i][j]!='s')continue;
      
      int posx=i,posy=j;
      //もしS[i][j]がｓなら探索を始める
      
      for(int d=0;d<8;d++){//方向ｄを決める
        
        posx=i;
        posy=j;
        
        for(int k=0;k<4;k++){
          posx+=dx[d],posy+=dy[d];
          
          if(posx<0||H<=posx||posy<0||W<=posy)break;//グリッドの外に出たら探索を打ち切る
  
          if(S[posx][posy]!=s[k+1])break;//文字列ｓとｋ文字目一致していなければ探索を打ち切る
          
          if(k==3){
            posx-=4*dx[d];
            posy-=4*dy[d];
            
            for(int cnt=0;cnt<5;cnt++){
              cout<<posx+1<<" "<<posy+1<<endl;
              posx+=dx[d];
              posy+=dy[d];
            }
            
            return 0;
          }
          
        }
        
      }
      
      
    }
  }
  
  cout<<-1<<endl;
}
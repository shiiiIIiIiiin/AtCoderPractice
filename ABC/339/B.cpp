#include<bits/stdc++.h>
using namespace std;

int main(){
  int H,W,N;cin>>H>>W>>N;
  char F[H][W];
  for(int i=0;i<H;i++)for(int j=0;j<W;j++)F[i][j]='.';
  
  int posx=0,posy=0,d=0;
  
  int dx[4]={0,1,0,-1},dy[4]={-1,0,1,0};
  
  for(int i=0;i<N;i++){
    if(F[posy][posx]=='.'){
      F[posy][posx]='#';
      d++;
      posx=(posx+dx[(d+4)%4]+W)%W;posy=(posy+dy[(d+4)%4]+H)%H;
      
    }else{
      F[posy][posx]='.';
      d--;
      posx=(posx+dx[(d+4)%4]+W)%W;posy=(posy+dy[(d+4)%4]+H)%H;
      
    }
  
  }
  
  
  for(int i=0;i<H;i++){
    for(int j=0;j<W;j++)cout<<F[i][j];
    cout<<endl;
  }
  
  
  
  
}


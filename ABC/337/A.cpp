#include<bits/stdc++.h>
using namespace std;

int main(void){
  int N;
  scanf("%d",&N);
  
  int i,sx=0,sy=0,x,y;
  for(i=0;i<N;i++){
    scanf("%d%d",&x,&y);
    sx+=x;
    sy+=y;
  }
  
  if(sx>sy)printf("Takahashi\n");
  else if(sx==sy)printf("Draw\n");
  else printf("Aoki\n");
  
  return 0;
}
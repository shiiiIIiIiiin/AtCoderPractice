#include<stdio.h>

int main(void){
  int N,D;
  scanf("%d%d",&N,&D);
  
  int X[N][D],i,j,l,m,d=0,count=0;
  
  for(i=0;i<N;i++){
    for(j=0;j<D;j++){
      scanf("%d",&X[i][j]);
    }
  }
  
  
  for(i=0;i<N-1;i++){
    for(j=i+1;j<N;j++){
      d=0;
      for(l=0;l<D;l++){
        d+=(X[i][l]-X[j][l])*(X[i][l]-X[j][l]);
      }
      
      for(m=0;m*m<=d;m++){
        if(m*m==d){
          count++;
        }
      }
     
      //dを０にする
    }
  }
  printf("%d",count);
  return 0;
}
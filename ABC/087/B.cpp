#include<stdio.h>

int main(void){
  int A,B,C,X,i,j,k,ans=0;
  scanf("%d%d%d%d",&A,&B,&C,&X);
  
  for(i=0;i<=A;i++){
    for(j=0;j<=B;j++){
      for(k=0;k<=C;k++){
        if(500*i+100*j+50*k==X) ans++;
      }
    }
  }
  printf("%d",ans);
  return 0;
}
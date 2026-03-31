#include<stdio.h>
int main(void){
  int N;
  scanf("%d",&N);
  int f=0,i,j;
  
  for(i=1;i<=9;i++){
    for(j=1;j<=9;j++){
      if(i*j==N) f=1;
    }
  }
  
  if(f==1){
    printf("Yes");
  }else{
    printf("No");
  }
  return 0;
}
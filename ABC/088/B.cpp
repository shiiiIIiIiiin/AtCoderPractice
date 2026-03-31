#include<stdio.h>
int main(void){
  int N;
  scanf("%d",&N);
  int a[N],i,j,x;
  for(i=0;i<N;i++){
    scanf("%d",&a[i]);
  }
  
  for(i=0;i<N;i++){
    for(j=N-1;j>i;j--){
      if(a[j]>a[j-1]){
        x=a[j-1];
        a[j-1]=a[j];
        a[j]=x;
      }
    }
  }
  
  int alice=0,bob=0;
  for(i=0;i<N;i++){
    if(i%2==0)alice+=a[i];
    else bob+=a[i];
  }
  
  printf("%d",alice-bob);
  return 0;
}
#include<stdio.h>
int main(void){
  int N,K;
  scanf("%d%d",&N,&K);
  int l[N],i,j,x;
  for(i=0;i<N;i++){
    scanf("%d",&l[i]);
  }
  
  for(i=0;i<N;i++){
    for(j=N-1;j>i;j--){
      if(l[j]>l[j-1]){
        x=l[j-1];
        l[j-1]=l[j];
        l[j]=x;
      }
    }
  }
  
 int sum=0;
 for(i=0;i<K;i++){
   sum+=l[i];
 }
 
 printf("%d",sum);
  return 0;
}
#include<stdio.h>
#include<stdbool.h>
int main(void){
  int N;
  scanf("%d",&N);
  int d[N],i;
  for(i=0;i<N;i++){
    scanf("%d",&d[i]);
  }
  
  int a[100]={0},ans=0;
  for(i=0;i<N;i++){
    if(a[d[i]]==0) ans++;
    a[d[i]]=1;
  }
  printf("%d",ans);
  return 0;
}
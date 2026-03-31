#include<stdio.h>
int main(void){
  int N,A,B,a[5],n=1,i,j,k,s=0,ans=0;
  scanf("%d%d%d",&N,&A,&B);
  
  
  for(i=0;i<=N;i++){
    for(j=0;j<5;j++){
      a[j]=(i/n)%10;
      n*=10;
      s+=a[j];
    }
  
    if(A<=s&&s<=B)ans+=i;
    n=1;
    s=0;
  }
  
  printf("%d",ans);
  return 0;
}
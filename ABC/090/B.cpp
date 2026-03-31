#include<stdio.h>

int main(void){
  int A,B;
  scanf("%d%d",&A,&B);
  
  int count=0,i,j,n,a[5],ans;
  
  for(i=A;i<=B;i++){
    n=i;
    
    for(j=0;j<5;j++){
      a[j]=n%10;
      n/=10;
    }
    
    if(a[0]==a[4]&&a[1]==a[3]) ans++;
    
  }
  printf("%d",ans);
  return 0;
}
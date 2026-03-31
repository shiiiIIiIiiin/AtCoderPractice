#include<stdio.h>
int main(void){
  int N,x;
  scanf("%d%d",&N,&x);
  int a[N],i,j,p;
  for(i=0;i<N;i++){
    scanf("%d",&a[i]);
  }
  
  for(i=0;i<N;i++){
    for(j=N-1;j>i;j--){
      if(a[j]<a[j-1]){
        p=a[j-1];
        a[j-1]=a[j];
        a[j]=p;
      }
    }
  }
  
 int ans=0;
 for(i=0;i<N;i++){
   if(a[i]<=x){
     ans++;
     x-=a[i];
     }else{
       break;
     }
     
     if(i==N-1&&x>0){
       ans--;
     }
 }
 
 printf("%d",ans);
  return 0;
}
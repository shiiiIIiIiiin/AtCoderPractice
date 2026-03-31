#include<stdio.h>
#include<math.h>
int main(void){
  int N;
  scanf("%d",&N);
  int a[N],i,max=0,min=0;
  for(i=0;i<N;i++){
    scanf("%d",&a[i]);
    if(i==0) min=a[0];
    if(max<a[i]) max=a[i];
    if(min>a[i]) min=a[i];
  }
 printf("%d",max-min);
 return 0;
  
}
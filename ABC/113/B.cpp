#include<stdio.h>
#include<math.h>
int main(void){
  int N,T,A;
  scanf("%d",&N);
  scanf("%d %d",&T,&A);
  int H[N],ans,i;
  for(i=0;i<N;i++){
    scanf("%d",&H[i]);
  }
  double min,t[N];
  
  min=fabs(A-(T-H[0]*0.006));
  
  for(i=0;i<N;i++){
     t[i]=T-H[i]*0.006;
    if(fabs(A-t[i])<=min){
      ans=i+1;
      min=fabs(A-t[i]);
    }
  }
  
  printf("%d",ans);
  return 0;
}
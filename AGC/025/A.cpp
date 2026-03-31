#include<stdio.h>
int main(void){
  int N;
  scanf("%d",&N);
  
  int A,B,sum=0,min=10000,a[6]={0},b[6]={0},n1,n2,i;
  
  for(A=1;A<=N/2;A++){
    B=N-A;
    n1=A;
    n2=B;
    i=0;
    sum=0;
    while(n1!=0){
      a[i]=n1%10;
      n1/=10;
      i++;
    }
    
    i=0;
    
    while(n2!=0){
      b[i]=n2%10;
      n2/=10;
      i++;
    }
    
    
    
    for(i=0;i<6;i++){
      sum=sum+a[i]+b[i];
    }
    
    if(min>sum)min=sum;
  }
  printf("%d",min);
  return 0;
}
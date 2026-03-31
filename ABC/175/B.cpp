#include<stdio.h>
#include<math.h>
int main(void){
  int N;
  scanf("%d",&N);
  int L[N],i,j,k;
  for(i=0;i<N;i++){
    scanf("%d",&L[i]);
  }

  int ans=0;
  for(i=0;i<N-2;i++){
    for(j=i+1;j<N-1;j++){
      for(k=j+1;k<N;k++){
        if(abs(L[i]-L[j])<L[k]&&L[k]<L[i]+L[j]&&L[i]!=L[j]&&L[i]!=L[k]&&L[j]!=L[k]){
          ans++;
        }
      }
    }
  }
/*  for(i=0;i<count;i++){
  printf("%d  ",a[i]);
  }*/
  printf("%d",ans);
  return 0;
}
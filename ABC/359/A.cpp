#include<stdio.h>
#include<string.h>

int main(void){
  int n;
  scanf("%d",&n);
  char S[256];
  int ans=0;
  for(int i=0;i<n;i++){
    scanf("%s",S);
    if(strcmp(S,"Takahashi")==0)ans++;
  }
  printf("%d",ans);
  return 0;
}
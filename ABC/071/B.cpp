#include<stdio.h>
int main(void){
  char S[100100];
  scanf("%s",S);
  
  int a[26]={0},i;
  for(i=0;S[i]!='\0';i++){
    if(a[S[i]-'a']==0){
      a[S[i]-'a']=1;
    }
  }
  
  for(i=0;i<26;i++){
    if(a[i]==0){ 
    printf("%c",(char)(i+'a'));
    break;
    }
    if(i==25){
      printf("None");
    }
  }
  return 0;
}
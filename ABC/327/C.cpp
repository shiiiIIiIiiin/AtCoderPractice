#include<bits/stdc++.h>
using namespace std;

int main(){
  int A[9][9],i,j;
  for(i=0;i<9;i++){
    for(j=0;j<9;j++)cin>>A[i][j];
  }
  
  bool ans=true;
  
  for(i=0;i<9;i++){//横成分の判定
    bool k[10];
    for(j=0;j<10;j++)k[j]=false;
    
    for(int l=0;l<9;l++){
      if(k[A[i][l]])ans=false;
      k[A[i][l]]=true;
    }
    
  }
  
   for(i=0;i<9;i++){//縦成分の判定
    bool k[10];
    for(j=0;j<10;j++)k[j]=false;
    
    for(int l=0;l<9;l++){
      if(k[A[l][i]])ans=false;
      k[A[l][i]]=true;
    }
    
  }
  
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
      
      bool k[10];
      for(int p=0;p<10;p++)k[p]=false;
      
      for(int n=3*i;n<3*i+3;n++){
        for(int m=3*j;m<3*j+3;m++){
          
          if(k[A[n][m]])ans=false;
          k[A[n][m]]=true;
        }
      }
    }
  }
  
  cout<<(ans ? "Yes":"No")<<endl;
}
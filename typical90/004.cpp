#include<bits/stdc++.h>
using namespace std;


int main(void){
  int i,j,H,W;
  cin>>H>>W;
  int A[H][W];
  
  for(i=0;i<H;i++){
    for(j=0;j<W;j++)cin>>A[i][j];
  }
  
  int c[W]={0},d[H]={0};
  
  for(i=0;i<W;i++)for(j=0;j<H;j++)c[i]+=A[j][i];
  for(i=0;i<H;i++)for(j=0;j<W;j++)d[i]+=A[i][j];
  
  
  for(i=0;i<H;i++){
    for(j=0;j<W;j++)cout<<d[i]+c[j]-A[i][j]<<" ";
    cout<<endl;
  }
  
}
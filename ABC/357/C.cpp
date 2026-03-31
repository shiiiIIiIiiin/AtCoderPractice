#include<bits/stdc++.h>
using namespace std;

void siro(int N,int x,int y,vector<vector<char>> &A){
  for(int i=0;i<pow(3,N-1);i++){
    for(int j=0;j<pow(3,N-1);j++)A[x+i][y+j]='.';
  }
  return;
}


void carpet(int N,int x,int y,vector<vector<char>> &A){
  
  if(N==1){
    A[x][y]=A[x+1][y]=A[x+2][y]=A[x][y+1]=A[x+2][y+1]=A[x][y+2]=A[x+1][y+2]=A[x+2][y+2]='#';
    A[x+1][y+1]='.';
    return;
  }
  
  for(int i=0;i<3;i++)for(int j=0;j<3;j++){
    if(i==1&&j==1)siro(N,x+pow(3,N-1),y+pow(3,N-1),A);
    else{
      carpet(N-1,x+i*pow(3,N-1),y+j*pow(3,N-1),A);
    }
  }
  return;
}

int main(){


 int N;cin>>N;
 int scale=pow(3,N);

 vector<vector<char>> A(scale,vector<char>(scale,'!'));
 
 if(N==0){
   cout<<"#";
   return 0;
 }
 carpet(N,0,0,A);
 
 for(int i=0;i<pow(3,N);i++){
   for(int j=0;j<pow(3,N);j++)cout<<A[i][j];
   cout<<endl;
 }
 

}
#include<bits/stdc++.h>
using namespace std;

int main(){
 int N;
 cin>>N;
 
 char A[N][N],B[N][N];
 int i,j;
 for(i=0;i<N;i++){
   for(j=0;j<N;j++){
     cin>>A[i][j];
   }
 }
 for(i=0;i<N;i++){
   for(j=0;j<N;j++){
     cin>>B[i][j];
   }
 }
 
 for(i=0;i<N;i++){
   for(j=0;j<N;j++){
     if(A[i][j]!=B[i][j])cout<<i+1<<" "<<j+1<<endl;
   }
 }
}
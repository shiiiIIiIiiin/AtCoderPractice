#include<bits/stdc++.h>
using namespace std;

int main(){
 int N,M,i,j;
 cin>>N>>M;
 int X[N][M],A[M];
 for(i=0;i<M;i++)cin>>A[i];
 for(i=0;i<N;i++){
   for(j=0;j<M;j++)cin>>X[i][j];
 }

 
 for(i=0;i<M;i++){
   int cnt=0;
   for(j=0;j<N;j++)cnt+=X[j][i];
   if(cnt<A[i]){
     cout<<"No"<<endl;
     return 0;
   }
 }
 
 cout<<"Yes"<<endl;
 
}
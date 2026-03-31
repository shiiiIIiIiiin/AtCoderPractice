#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,T;cin>>N>>T;
  vector<int> A(T);
  for(int i=0;i<T;i++)cin>>A[i];
 
  int card[N+1][N+1];
  for(int i=1;i<=N;i++)for(int j=1;j<=N;j++)card[i][j]=N*(i-1)+j;
  
  for(int i=0;i<T;i++){
    int a=(A[i]-1)/N+1,b=(A[i]-1)%N+1;
    
    card[a][b]=-1;
    
   if(a==b){
     bool flag=true;
     
     for(int k=1;k<=N;k++){
       if(card[k][k]!=-1){
         flag=false;
         break;
       }
     }
     
     if(flag){
       cout<<i+1<<endl;
       return 0;
     }
   }
   
   if(a+b==N+1){
     bool flag=true;
     
     for(int k=1;k<=N;k++){
       if(card[k][N+1-k]!=-1){
         flag=false;
         break;
       }
     }
     
       if(flag){
         cout<<i+1<<endl;
         return 0;
       }
   }
   
   bool tate=true,yoko=true;
   
   for(int j=1;j<=N;j++){
     if(card[a][j]!=-1)yoko=false;
     if(card[j][b]!=-1)tate=false;
   }
   
   if(tate||yoko){
     cout<<i+1<<endl;
     return 0;
   }
   
   
   /*
   for(int k=1;k<=N;k++){
     for(int l=1;l<=N;l++)cout<<card[k][l]<<" ";
     cout<<endl;
   }
   
   cout<<endl;
   */
   
  }
  
  cout<<-1<<endl;
  return 0;
}
#include<bits/stdc++.h>
using namespace std;
int main(){
 int N,X;
 cin>>N>>X;
 int A[N+1],i;
 for(i=1;i<=N;i++)cin>>A[i];
 
 int L=1,R=N,M=0;
 
 while(L<=R){
   M=(L+R)/2;
   if(X<A[M])R=M-1;
   else if(X==A[M]){
     cout<<M<<endl;
     break;
   }
   else L=M+1;
 }
 
}
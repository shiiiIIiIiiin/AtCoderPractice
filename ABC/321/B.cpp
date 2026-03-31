#include<bits/stdc++.h>
using namespace std;

int main(){
   int N,X;cin>>N>>X;
   int A[N-1];
   for(int i=0;i<N-1;i++)cin>>A[i];
   sort(A,A+N-1);
   
   for(int i=0;i<=100;i++){
     int B[N];
     for(int j=0;j<N-1;j++)B[j]=A[j];
     B[N-1]=i;
     
     sort(B,B+N);
     
     int sum=0;
     for(int j=1;j<N-1;j++)sum+=B[j];
     
     if(sum>=X){
       cout<<i<<endl;
       return 0;
     }
   }
   
   cout<<-1<<endl;
}
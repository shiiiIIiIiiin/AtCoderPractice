#include<bits/stdc++.h>
using namespace std;

int main(){
 int N,K;
 cin>>N>>K;
 int A[N],i;
 for(i=0;i<N;i++)cin>>A[i];
 
 int L=0,R=1000000000;
 int M=0;
 
 while(L<R){
    long int sum=0;
    M=(L+R)/2;
    
    for(int i=0;i<N;i++)sum+=M/A[i];
    
    if(sum<K)L=M+1;
    else if(sum>=K)R=M;
  }
  
 cout<<L<<endl;
}
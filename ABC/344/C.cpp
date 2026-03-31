#include<bits/stdc++.h>
using namespace std;
int main(){
  int N,M,L,Q,i;
  cin>>N;
  int A[N];
 for(i=0;i<N;i++)cin>>A[i];
 cin>>M;
 int B[M];
 for(i=0;i<M;i++)cin>>B[i];
 cin>>L;
 int C[L];
 for(i=0;i<L;i++)cin>>C[i];
 cin>>Q;
 int X[Q];
 for(i=0;i<Q;i++)cin>>X[i];
 
 bool P[300000001];
 for(i=0;i<300000001;i++)P[i]=false;
 
 int j,k;
 
 for(i=0;i<N;i++){
   for(j=0;j<M;j++){
     for(k=0;k<L;k++){
       P[A[i]+B[j]+C[k]]=true;
     }
   }
 }
 
 for(i=0;i<Q;i++){
   cout<<(P[X[i]]?"Yes":"No")<<endl;
 }
 
}
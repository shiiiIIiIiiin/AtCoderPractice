#include<bits/stdc++.h>
using namespace std;


int main(void){
 long int N;cin>>N;
 long int i;
 
 vector<long long> A(N+2);for(i=1;i<=N;i++)cin>>A[i];
 A[0]=-1000000000000,A[N+1]=100'000'000'000;sort(A.begin(),A.end());
 
 long int Q;cin>>Q;
 vector<long long> B(Q);for(i=0;i<Q;i++)cin>>B[i];
 
 long int l,r,m;
 
 for(i=0;i<Q;i++){
  l=-1,r=N+1,m=(r+l)/2;
   while(r-l>1){//二分探索でB[i]以下最大のAの要素を求める
     m=(l+r)/2;
     if(A[m]<=B[i])l=m;
     else r=m;
   }
   
   long long ans=min(llabs(A[l]-B[i]),llabs(A[l+1]-B[i]));
   cout<<ans<<endl;
 }
 
}
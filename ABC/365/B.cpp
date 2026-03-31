#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
 vector<long long> A(N);
 for(int i=0;i<N;i++)cin>>A[i];
 int B[N];
 for(int i=0;i<N;i++)B[i]=A[i];
 
 sort(A.begin(),A.end());
 
 int ans=A[N-2];
 
 for(int i=0;i<N;i++){
   if(B[i]==ans)cout<<i+1<<endl;
 }
  return 0;
}
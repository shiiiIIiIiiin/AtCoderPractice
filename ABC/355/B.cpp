#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,M,i;
  cin>>N>>M;
  vector<int> A(N),B(M);
  for(i=0;i<N;i++)cin>>A[i];
  for(i=0;i<M;i++)cin>>B[i];
  
  sort(A.begin(),A.end());
  sort(B.begin(),B.end());
  
  
  int ca=0,cb=0;
  
  bool flag=false;
  if(A[0]<B[0]){
    flag=true;//最後Aの時true
    ca++;
  }
  
  bool ans=true;
  
  while(true){
    //脱出判定
     if(ca==N)break;
    if(cb==M){
      if(ca<=N-2){
        ans=false;
    }
    break;
  }//脱出判定
   
    if(A[ca]<B[cb]){
      if(flag){
        ans=false;
      }
      flag=true;
      ca++;
    }else if(A[ca]>B[cb]){
      flag=false;
      cb++;
    }
  
  }
  
  
  cout<<(ans?"No":"Yes")<<endl;
}
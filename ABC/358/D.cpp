#include<bits/stdc++.h>
using namespace std;
int main(){
  int N,M;
  cin>>N>>M;
  vector<long int> A(N),B(M);
  long int i,j;
  for(i=0;i<N;i++)cin>>A[i];
  for(i=0;i<M;i++)cin>>B[i];
  
  sort(A.begin(),A.end());
  sort(B.begin(),B.end());
  
 
 i=0;
  j=0;
  long int sum=0;
  
    while(true){
      if(B[i]<=A[j]){
        sum+=A[j];
        i++;
        if(i==M)break;
      }//iを増やしてjも増やす
      
      j++;
      if(j==N){
        cout<<-1<<endl;
        return 0;
      }
    }
    
   
    cout<<sum<<endl;
}
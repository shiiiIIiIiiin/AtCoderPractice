#include<bits/stdc++.h>
using namespace std;

int main(){
 int N,K;
 cin>>N>>K;
 int A[N],count=0,ans=0,i,cnt=0;
 for(int i=0;i<N;i++)cin>>A[i];
 
 while(count<=N-1){
  for(i=count;i<N;i++){
    cnt+=A[count];
    count++;
    if(cnt+A[i+1]>K){
      ans++;
      cnt=0;
      break;
    }
  }
 }

 cout<<ans<<endl;

}

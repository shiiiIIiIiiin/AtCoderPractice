#include<bits/stdc++.h>
using namespace std;
int main(){
  int N,A;
  cin>>N>>A;
  int T[N];
  int i;
  for(i=0;i<N;i++)cin>>T[i];
  
  int ans[N];
  
  ans[0]=T[0]+A;
  for(i=0;i<N-1;i++){
    if(T[i+1]-T[i]>=A)ans[i+1]=T[i+1]+A;
    else ans[i+1]=ans[i]+A;
  }
  
  for(i=0;i<N;i++){
    cout<<ans[i]<<endl;
  }
}
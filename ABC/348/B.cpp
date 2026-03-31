#include<bits/stdc++.h>
using namespace std;
int main(){
  int N,i,j;
  cin>>N;
  int x[N],y[N];
  for(i=0;i<N;i++){
   cin>>x[i]>>y[i];
  }
  
  int ans=0;
  
  for(i=0;i<N;i++){
    int Max=0;
    for(j=0;j<N;j++){
    
    int D=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
    if(Max<D){
      Max=D;
      ans=j;
    }
  
    }
    cout<<ans+1<<endl;
    ans=0;
  }
  
}

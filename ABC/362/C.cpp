#include <bits/stdc++.h>
using namespace std;

int main(){
  long long N,i;
  cin>>N;
  long long L[N],R[N];
  
  for(i=0;i<N;i++)cin>>L[i]>>R[i];
  
  long long sum1=0,sum2=0;
  
  for(i=0;i<N;i++){
    sum1+=L[i];
    sum2+=R[i];
  }
  
  if(sum1<=0&&0<=sum2)cout<<"Yes"<<endl;
  else {
    cout<<"No"<<endl;
    return 0;
  }
    
    
  sum1=-sum1;
  
  i=0;
  while(sum1!=0){
    if(sum1<=R[i]-L[i]){
      L[i]+=sum1;
      sum1=0;
    }
    else{
      sum1=sum1-(R[i]-L[i]);
      L[i]=R[i];
      
     // cout<<sum1<<endl;
    }
    i++;
  }
  
  for(i=0;i<N;i++)cout<<L[i]<<" ";
  
}
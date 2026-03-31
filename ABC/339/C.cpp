#include<bits/stdc++.h>
using namespace std;
int main(){
  int N;
  cin>>N;
  long long A,i,min=0,sum=0;
  
  for(i=0;i<N;i++){
    cin>>A;
    sum+=A;
    if(min>sum)min=sum;
  }
  
  cout<<sum-min<<endl;
}
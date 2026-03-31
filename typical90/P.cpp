#include<bits/stdc++.h>
using namespace std;

int main(){
  long long N,A,B,C;cin>>N>>A>>B>>C;
  
  long long min=1'000'000;
  
  for(long long i=0;i<=10000;i++)for(long long j=0;j<=10000;j++){
     if(N-A*i-B*j<0)continue;
     if((N-A*i-B*j)%C==0&&min>i+j+((N-A*i-B*j)/C))min=i+j+((N-A*i-B*j)/C);
  }
  
  cout<<min<<endl;
}
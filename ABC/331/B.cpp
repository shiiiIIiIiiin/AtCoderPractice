#include<bits/stdc++.h>
using namespace std;
int main(){
  int N,S,M,L;
  cin>>N>>S>>M>>L;
  
  int min=10000000,i,j,k;
  
  for(i=0;i<=N/6+1;i++){
    for(j=0;j<=N/8+1;j++){
      for(k=0;k<=N/12+1;k++){
        if(6*i+8*j+12*k>=N&&min>i*S+j*M+k*L)min=i*S+j*M+k*L;
      }
    }
  }
  cout<<min<<endl;
}
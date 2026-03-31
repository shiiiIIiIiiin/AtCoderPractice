#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;
  cin>>N;
  
  int i=0,j=0,k=0;
  
  for(i=0;i<=N;i++){
    for(j=0;j<=N;j++){
      for(k=0;k<=N;k++){
        if(i+j+k<=N)cout<<i<<" "<<j<<" "<<k<<endl;
      }
    }
  }
}
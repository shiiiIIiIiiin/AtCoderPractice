#include<bits/stdc++.h>
using namespace std;

int A,B,D;

int main(){
  cin>>A>>B>>D;
  
  for(int i=0;i<(B-A)/D+1;i++){
    cout<<A+D*i<<" ";
  }
  //cout<<endl;
}
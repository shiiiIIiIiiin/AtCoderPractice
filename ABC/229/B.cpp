#include<bits/stdc++.h>
using namespace std;

int main(){
  long long A,B;cin>>A>>B;
  
  while(A!=0&&B!=0){
    if(A%10+B%10>=10){
      cout<<"Hard"<<endl;
      return 0;
    }
     A/=10;
     B/=10;

  }
  
  cout<<"Easy"<<endl;
}
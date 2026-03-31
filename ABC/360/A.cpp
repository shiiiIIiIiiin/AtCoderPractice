#include<bits/stdc++.h>
using namespace std;
#define MOD 1'000'000'007

int main(){
  char S;
  
  int i;
  for(i=0;i<3;i++){
    cin>>S;
    if(S=='R'){
      cout<<"Yes"<<endl;
      return 0;
    }
    if(S=='M'){
      cout<<"No"<<endl;
      return 0;
    }
  }
}

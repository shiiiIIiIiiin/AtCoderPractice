#include<bits/stdc++.h>
using namespace std;

int main(){
  double X;cin>>X;
  X*=1000;
  int cnt=0;
  
  while(true){
    if((int)X%10==0&&(int)X!=0)cnt++;
    else if((int)X==0)break;
    else break;
    X/=10;
  }
  
  X/=1000;
  
  for(int i=0;i<cnt;i++)X*=10;
  
  cout<<X<<endl;
}
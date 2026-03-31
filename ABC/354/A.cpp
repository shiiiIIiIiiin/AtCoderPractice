#include<bits/stdc++.h>
using namespace std;
int main(){
  int H;
  cin>>H;
  int scale=2;
  int cnt=0;
  
  while(scale-1<=H){
    cnt++;
    scale*=2;
  }
  
  cout<<cnt+1<<endl;
}
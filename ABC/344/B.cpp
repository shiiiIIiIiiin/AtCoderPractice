#include<bits/stdc++.h>
using namespace std;

int main(){
  vector<int> a;
  int i=0;
  
  while(true){
    cin>>i;
    a.push_back(i);
    if(i==0)break;
  }
  
  for(i=a.size()-1;i>=0;i--){
    cout<<a[i]<<endl;
  }
}
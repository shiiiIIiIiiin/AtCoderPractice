#include<bits/stdc++.h>
using namespace std;
int main(){
  int H,W,i,j;
  cin>>H>>W;
  vector<char> a(W);
  
  for(i=0;i<W+2;i++)cout<<'#';
  cout<<endl;
  
  for(i=0;i<H;i++){
    cout<<'#';
    
    for(j=0;j<W;j++){
      cin>>a.at(j);
      cout<<a.at(j);
    }
    cout<<'#'<<endl;
  }
  
   for(i=0;i<W+2;i++)cout<<'#';
   cout<<endl;
}
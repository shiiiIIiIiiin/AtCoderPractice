#include<bits/stdc++.h>
using namespace std;
int main(){
  int H,W,i,j,k;
  cin>>H>>W;
  vector<vector<char>> a(H,vector<char>(W));
  for(i=0;i<H;i++){
    for(j=0;j<W;j++){
      cin>>a.at(i).at(j);
    }
  }
  
  bool can=true;
  
  for(i=0;i<H;i++){
    for(j=0;j<W;j++){
      if(a.at(i).at(j)=='#')can=false;
    }
    
    if(can){
      for(k=0;k<W;k++)a.at(i).at(k)='d';
    }
    can=true;
  }
  
  for(i=0;i<W;i++){
    for(j=0;j<H;j++){
      if(a.at(j).at(i)=='#')can=false;
    }
    
    if(can){
      for(k=0;k<H;k++)a.at(k).at(i)='d';
    }
    can=true;
  }
  
  for(i=0;i<H;i++){
    for(j=0;j<W;j++){
      if(a.at(i).at(j)!='d')cout<<a.at(i).at(j);
    }
    cout<<endl;
  }
}
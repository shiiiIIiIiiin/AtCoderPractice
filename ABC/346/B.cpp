#include<bits/stdc++.h>
using namespace std;

const string t="wbwbwwbwbwbw";

int main(){
  int　w,b,i,j;
  cin>>w>>b;
  bool can=false;
  for(i=0;i<(int)t.size();i++){
    int nw=0;
    int nb=0;
    for(j=0;j<w+b;j++){
     if(t.at((i+j)%t.size())=='w')nw++;
     else nb++;
    }
    if(nw==w&&nb==b){
      can=true;
      break;
    }
  }
  
  if(can)cout<<"Yes"<<endl;
  else cout<<"No"<<endl;
}
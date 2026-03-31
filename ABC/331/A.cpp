#include<bits/stdc++.h>
using namespace std;

int main(){
  int M,D,y,m,d;
  cin>>M>>D>>y>>m>>d;
  int a,b,c;
  if(d==D){
    c=1;
    if(m==M){
      a=y+1;b=1;
    }else {
      a=y;b=m+1;
    }
  }else{
    a=y;
    b=m;
    c=d+1;
    
  }

cout<<a<<" "<<b<<" "<<c<<endl;

}
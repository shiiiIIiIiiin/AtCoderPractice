#include <bits/stdc++.h>
using namespace std;

bool atari(int a,int d,int g,int j){
  bool can;
  if(d<=g||j<=a){
    can=false;
  }
  else{
   can=true;
  }
  return can;
}

int main() {
  int a,b,c,d,e,f,g,h,i,j,k,l;
  cin>>a>>b>>c>>d>>e>>f>>g>>h>>i>>j>>k>>l;
  
  
  bool f1,f2,f3;
  f1=atari(a,d,g,j);
  f2=atari(b,e,h,k);
  f3=atari(c,f,i,l);
  
  if(f1&&f2&&f3)cout<<"Yes"<<endl;
  else cout<<"No"<<endl;
}

#include <bits/stdc++.h>
using namespace std;

int f(int x){
  return x*x;
}

int main(){
  int x[3],y[3];
  
  for(int i=0;i<3;i++)cin>>x[i]>>y[i];
  
  int a=f(x[0]-x[1])+f(y[0]-y[1]),b=f(x[0]-x[2])+f(y[0]-y[2]),c=f(x[1]-x[2])+f(y[2]-y[1]);
  
  if(a==b+c||b==a+c||c==a+b)cout<<"Yes"<<endl;
  else cout<<"No"<<endl;
}
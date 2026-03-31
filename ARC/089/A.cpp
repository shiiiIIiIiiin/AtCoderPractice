#include<bits/stdc++.h>
using namespace std;
int main(){
  int N,i;
  cin>>N;
  vector<int> t(N+1),x(N+1),y(N+1);
  for(i=1;i<N+1;i++)cin>>t.at(i)>>x.at(i)>>y.at(i);
  t.at(0)=x.at(0)=y.at(0)=0;
  bool can=true;
  
  for(i=0;i<N;i++){
    int X=abs(x.at(i)-x.at(i+1)),Y=abs(y.at(i)-y.at(i+1)),T=t.at(i+1)-t.at(i);
    if(X+Y>T||(T-(X+Y))%2!=0)can=false;
  }
  
  if(can)cout<<"Yes"<<endl;
  else cout<<"No"<<endl;
  
}
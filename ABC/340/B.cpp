#include<bits/stdc++.h>
using namespace std;

int main(){
  int Q;
  cin>>Q;
  long long a[Q],b[Q],i;
  vector<long long>c(0);
  for(i=0;i<Q;i++)cin>>a[i]>>b[i];
  
  for(i=0;i<Q;i++){
    if(a[i]==1)c.push_back(b[i]);
    else{
      cout<<c.at(c.size()-b[i])<<endl;
    }
  }

}
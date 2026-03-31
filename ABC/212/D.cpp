#include<bits/stdc++.h>
using namespace std;

int main(){
  int Q;cin>>Q;
  priority_queue<long long,vector<long long>,greater<long long>> Bag;
  
  long long sum=0;
  
  for(int i=0;i<Q;i++){
    int q;cin>>q;
    
    if(q==1){
      long long x;cin>>x;
      Bag.push(x-sum);
    }
    if(q==2){
      long long x;cin>>x;
      sum+=x;
    }
    
    if(q==3){
      long long k=Bag.top();Bag.pop();
      cout<<k+sum<<endl;
    }
    
    
  }
  
  return 0;
}
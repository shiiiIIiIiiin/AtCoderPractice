#include<bits/stdc++.h>
using namespace std;

int main(){
  long long D;cin>>D;
  
  long long ans=1'000'000'000'000'000'000;
  
  for(long long x=0;x*x<=D;x++){
    long long l=0,r=sqrt(D),m;
    
    while(r-l>1){
      m=(r+l)/2;
      if(x*x+m*m-D>0)r=m;
      else l=m;
    }
    
    long long kouho=min(llabs(x*x+l*l-D),llabs(x*x+r*r-D));
    
    ans=min(ans,kouho);
  }
  
  cout<<ans<<endl;
  
  
}
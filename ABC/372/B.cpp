#include<bits/stdc++.h>
using namespace std;

int main() {
  int M;cin>>M;
  int cnt;
  
  vector<long long> power3(12);
  
  long long p=1;
  
  for(int i=0;i<12;i++){
    power3[i]=p;
    p*=3;
  }
  
  vector<int> ans;
  cnt=11;
  
  while(M!=0){
    
    for(int i=0;i<M/power3[cnt];i++)ans.push_back(cnt);
    M-=(M/power3[cnt])*power3[cnt];
    
    cnt--;
  }
  
  cout<<ans.size()<<endl;
  for(auto x:ans)cout<<x<<" ";
  
}
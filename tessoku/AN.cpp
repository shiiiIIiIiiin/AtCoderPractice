#include<bits/stdc++.h>
using namespace std;

int main(){
  int n;cin>>n;
  long long ans=0;
  vector<long long> length(101,0);
  for(int i=0;i<n;i++){
    long long a;cin>>a;
    length[a]++;
  }
  for(int i=1;i<=100;i++){
    if(length[i]>=3){
      ans+=length[i]*(length[i]-1)*(length[i]-2)/6;
    }
  }
  cout<<ans<<endl;
  return  0;
}
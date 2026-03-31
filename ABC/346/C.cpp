#include<bits/stdc++.h>
using namespace std;
int main(){
  int N,K,i;
  cin>>N>>K;
  
  set<int> st;
  for(i=0;i<N;i++){
    int a;
    cin>>a;
    
   if(a<=K) st.insert(a);
  }
  
  long int ans=(long long)K*(K+1)/2;
  
  for(int i:st)ans-=i;
  
  cout<<ans<<endl;
  
}
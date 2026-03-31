#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,Q;cin>>N>>Q;
  string S;cin>>S;
  vector<int> cnt(N+1,0);
  
  for(int i=0;i<N;i++){
    cnt[i]=cnt[i-1];
    if(i!=0&&S[i]==S[i-1])cnt[i]++;
  }
  
  //for(int i=0;i<N;i++)cout<<cnt[i]<<endl;
  
  for(;Q--;){
    int l,r;cin>>l>>r;
    l--,r--;
    cout<<cnt[r]-cnt[l]<<endl;
  }
  
}
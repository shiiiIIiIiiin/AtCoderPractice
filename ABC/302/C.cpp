#include<bits/stdc++.h>
#include<atcoder/all>
using namespace atcoder;
using namespace std;
using ll=long long;

int diff(string &S,string &T){
  int res=0;
  for(int i=0;i<S.size();i++)if(S[i]!=T[i])res++;
  return res;
}

int main(){
  int N,M;cin>>N>>M;
  vector<string> S(N);
  for(int i=0;i<N;i++)cin>>S[i];
  sort(S.begin(),S.end());
 
  do{
    bool can=true;
    
    for(int i=0;i<N-1;i++)if(diff(S[i],S[i+1])>=2)can=false;
    
    if(can){
      cout<<"Yes"<<endl;
      return 0;
    }
    
  }while(next_permutation(S.begin(),S.end()));
  
  cout<<"No"<<endl;
}
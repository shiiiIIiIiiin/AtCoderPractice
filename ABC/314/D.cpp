#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
  int N,Q;
  string S;cin>>N>>S>>Q;
  vector<int> t(Q),x(Q);
  vector<char> c(Q);
  for(int i=0;i<Q;i++)cin>>t[i]>>x[i]>>c[i];
  int last=0;
  
  for(int i=0;i<Q;i++)if(t[i]!=1)last=i;
  
  for(int i=0;i<Q;i++){
    if(t[i]==1){
      S[x[i]-1]=c[i];
    }
    else if(t[i]==2&&i==last){
      for(int j=0;j<N;j++)if(isupper(S[j]))S[j]=char(S[j]-'A'+'a');
    }
    else if(t[i]==3&&i==last){
      for(int j=0;j<N;j++)if(!isupper(S[j]))S[j]=char(S[j]-'a'+'A');
    }
  }
  
  cout<<S<<endl;
}
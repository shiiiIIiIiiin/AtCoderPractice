#include<bits/stdc++.h>
#include<atcoder/all>
using namespace atcoder;
using namespace std;

int main(){
  int N;cin>>N;
  vector<int> x(N),y(N);
  for(int i=0;i<N;i++)cin>>x[i]>>y[i];
  
  for(int i=0;i<N-2;i++){
    for(int j=i+1;j<N-1;j++){
      for(int k=j+1;k<N;k++){
        if((x[i]-x[j])*(y[k]-y[j])==(y[i]-y[j])*(x[k]-x[j])){
          cout<<"Yes"<<endl;
          return 0;
        }
      }
    }
  }
  
  cout<<"No"<<endl;
}
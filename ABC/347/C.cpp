#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,A,B;cin>>N>>A>>B;
  vector<int> D(N);
  for(int i=0;i<N;i++)cin>>D[i];
  for(int i=0;i<N;i++)D[i]=D[i]%(A+B);
  sort(D.begin(),D.end());
  
  bool can=false;
  for(int i=0;i<N-1;i++){
    if(D[i+1]-D[i]>B)can=true;
  }
  
  if(D[0]-(D[N-1]-(A+B))>B)can=true;
  
  cout<<(can ? "Yes":"No")<<endl;
}
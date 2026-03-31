#include<bits/stdc++.h>
using namespace std;
int main(){
  int N;
  cin>>N;
  vector<int>A(N);
  for(int i=0;i<N;i++){
    cin>>A.at(i);
  }
  
  int H=0;
  
  for(int i=0;i<N;i++){
    H+=A.at(i);
  }
  
  H/=N;
  
  for(int i=0;i<N;i++)cout<<abs(A[i]-H)<<endl;
  
  
}
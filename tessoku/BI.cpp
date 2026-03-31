#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,M;
  cin>>N>>M;
  int A[M],B[M];
  for(int i=0;i<M;i++)cin>>A[i]>>B[i];
  
  vector<vector<int>> w(N,vector<int>(0));
  
  for(int i=0;i<M;i++){
    w.at(A[i]-1).push_back(B[i]);
    w.at(B[i]-1).push_back(A[i]);
  }
  
  for(int i=0;i<N;i++){
    cout<<i+1<<":{";
    for(int j=0;j<w.at(i).size();j++){
      cout<<w.at(i).at(j);
      if(j!=w.at(i).size()-1)cout<<", ";
    }
    cout<<"}"<<endl;
  }
  
}
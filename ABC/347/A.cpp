#include<bits/stdc++.h>
using namespace std;

int n,k;

int main(){
  cin>>n>>k;
  int A[n],i;
  for(i=0;i<n;i++)cin>>A[i];
  
  vector<int> a;
  for(auto i:A)if(i%k==0)a.push_back(i/k);
  
  for(i=0;i<a.size();i++)cout<<a[i]<<" ";
  cout<<endl;
}
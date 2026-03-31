#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
  vector<int> A(4);
  for(int i=0;i<4;i++)cin>>A[i];
  sort(A.begin(),A.end());
  
  if((A[0]==A[1]&&A[1]==A[2]&&A[2]!=A[3])||(A[3]==A[1]&&A[1]==A[2]&&A[0]!=A[1])||(A[1]==A[0]&&A[2]==A[3]&&A[1]!=A[2]))cout<<"Yes"<<endl;
  else cout<<"No"<<endl;
}
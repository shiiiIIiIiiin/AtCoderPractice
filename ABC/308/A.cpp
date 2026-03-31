#include <bits/stdc++.h>
using namespace std;

int main(){
  vector<int> A(8);
  for(int i=0;i<8;i++)cin>>A[i];
  
  if(A[0]%25!=0||A[0]<100||675<A[0]){
    cout<<"No"<<endl;
    return 0;
  }
  
  for(int i=1;i<8;i++){
    if(A[i]%25!=0||A[i]<100||675<A[i]||A[i-1]>A[i]){
      cout<<"No"<<endl;
      return 0;
    }
  }
  
  cout<<"Yes"<<endl;
}
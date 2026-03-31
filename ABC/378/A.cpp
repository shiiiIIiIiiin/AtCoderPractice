#include<bits/stdc++.h>
using namespace std;

int main(){
  vector<int> A(4);
  for(int i=0;i<4;i++)cin>>A[i];
  
  sort(A.begin(),A.end());
  int ans=0;
  for(int i=0;i<4;i++){
    if(i<=2&&A[i]==A[i+1]){
      ans++;
      i++;
    }
  }
  cout<<ans<<endl;
}
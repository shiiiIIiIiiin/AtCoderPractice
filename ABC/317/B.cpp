#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  vector<int> A(N);
  for(int i=0;i<N;i++)cin>>A[i];
  sort(A.begin(),A.end());
  for(int i=0;i<N;i++){
    if(A[i]!=A[0]+i){
      cout<<A[0]+i<<endl;
      return 0;
    }
  }
}
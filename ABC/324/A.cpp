#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,i;
  cin>>N;
  int A[N];
  for(i=0;i<N;i++)cin>>A[i];
  for(i=0;i<N;i++){
    if(A[0]!=A[i]){
    cout<<"No"<<endl;
    return 0;
    }
  }
  cout<<"Yes"<<endl;
}
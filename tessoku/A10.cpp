#include<bits/stdc++.h>
using namespace std;
int main(){
  int N;
  cin>>N;
  
  int A[N],i;
  for(i=0;i<N;i++){
    cin>>A[i];
  }
 ;
  
  int max1[N],max2[N];
  max1[0]=A[0];
  max2[N-1]=A[N-1];
  
  for(i=1;i<N;i++)max1[i]=max(A[i],max1[i-1]);
  for(i=N-1;i>0;i--)max2[i-1]=max(A[i-1],max2[i]);
  
  int D;
  cin>>D;
  for(i=0;i<D;i++){
    int L,R;
    cin>>L>>R;
    cout<<max(max1[L-2],max2[R])<<endl;
  }
}
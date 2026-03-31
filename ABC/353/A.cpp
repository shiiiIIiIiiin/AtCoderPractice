#include<bits/stdc++.h>
using namespace std;

int main(){
 int N;
 cin>>N;
 int H[N];
 for(int i=0;i<N;i++)cin>>H[i];
 int ans=-1,max=-1;

 for(int i=0;i<N;i++){
  if(H[0]<H[i]){
    cout<<i+1<<endl;
    break;
 } 
 if(i==N-1)cout<<-1<<endl;
}


}

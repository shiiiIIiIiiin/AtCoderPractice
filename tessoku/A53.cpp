#include<bits/stdc++.h>
using namespace std;

int main(){
 int Q;
 cin>>Q;
 int q[Q],x[Q],i;
 for(i=0;i<Q;i++){
   cin>>q[i];
   if(q[i]==1)cin>>x[i];
 }
 
 priority_queue<int,vector<int>,greater<int>> T;
 
 for(i=0;i<Q;i++){
   if(q[i]==1){
     T.push(x[i]);
   }else if(q[i]==2){
     cout<<T.top()<<endl;
   }else{
     T.pop();
   }
 }
}
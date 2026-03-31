#include<bits/stdc++.h>
using namespace std;

int main() {
   int Q;cin>>Q;
   long long cnt[1000000];for(int i=0;i<1000000;i++)cnt[i]=0;
   set<int> S;
   
   for(int i=0;i<Q;i++){
     int q,x;cin>>q;
     
     if(q==1){
       cin>>x;
       S.insert(x);
       cnt[x]++;
     }else if(q==2){
       cin>>x;
       cnt[x]--;
       if(cnt[x]==0){
         S.erase(x);
       }
     }else{
       cout<<S.size()<<endl;
     }
     
     
   }
   
}
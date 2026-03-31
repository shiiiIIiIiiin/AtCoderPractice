#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  vector<long long> H(N);
  for(int i=0;i<N;i++)cin>>H[i];
  
  long long T=0;
  
  for(int i=0;i<N;i++){
      if(T%3==0){
        T++;
        H[i]--;
        if(H[i]<=0)continue;
        T++;
        H[i]--;
        if(H[i]<=0)continue;
        T++;
        H[i]-=3;
        if(H[i]<=0)continue;
      }
      else if(T%3==1){
        T++;
        H[i]-=1;
        if(H[i]<=0)continue;
        T++;
        H[i]-=3;
        if(H[i]<=0)continue;
      }
      else if(T%3==2){
        T++;
        H[i]-=3;
        if(H[i]<=0)continue;
      }
      
    
      T+=H[i]/5*3;
      H[i]%=5;
      
      if(H[i]==0)continue;
      else if(H[i]==1)T++;
      else if(H[i]==2){
        if(T%3==2)T++;
        else T+=2;
      }
      else if(H[i]==3){
        if(T%3==2)T++;
        else if(T%3==0)T+=3;
        else T+=2;
      }
      else if(H[i]==4){
        if(T%3==0)T+=3;
        else T+=2;
        
      }
  }
  
  cout<<T<<endl;
  
}
#include<bits/stdc++.h>
using namespace std;


int main(void){
  long long Sx,Sy,Tx,Ty,ans=0;
  cin>>Sx>>Sy>>Tx>>Ty;
  long long a,b,hantei=Sx+Sy;
  b=llabs(Sx-Tx);
  a=llabs(Sy-Ty);
  
  if(a>=b)ans=a;
  else if(hantei%2==0&&Tx-Sx>=0){//タイルの左側からスタートの時
    ans=(b-a)/2+a;
  }else if(hantei%2==0&&Tx-Sx<0){//タイルの右側からスタートの時
    ans=(b-a+1)/2+a;
  }else if(hantei%2==1&&Tx-Sx>=0){
    ans=(b-a+1)/2+a;
  }else{
    ans=(b-a)/2+a;
  }
  
  cout<<ans<<endl;
  
  
}
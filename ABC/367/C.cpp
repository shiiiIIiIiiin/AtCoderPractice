#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,K;cin>>N>>K;
  int R[8];for(int i=0;i<8;i++)R[i]=1;
  for(int i=0;i<N;i++)cin>>R[i];
  
  vector<vector<long long>> ans;
  
  int i0,i1,i2,i3,i5,i4,i6,i7;
  
  for(i0=1;i0<=R[0];i0++){
    for(i1=1;i1<=R[1];i1++){
      for(i2=1;i2<=R[2];i2++){
        for(i3=1;i3<=R[3];i3++){
          for(i4=1;i4<=R[4];i4++){
            for(i5=1;i5<=R[5];i5++){
              for(i6=1;i6<=R[6];i6++){
                for(i7=1;i7<=R[7];i7++){
                  
                  int sum=i0+i1+i2+i3+i4+i5+i6+i7;
                  
                  sum-=8-N;
                  
                  
                  
                  if(sum%K==0){
                    vector<long long> p={i0,i1,i2,i3,i4,i5,i6,i7};
                    ans.push_back(p);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  
  
  for(int i=0;i<ans.size();i++){
    for(int j=0;j<N;j++)cout<<ans[i][j]<<" ";
    cout<<endl;
  }
}
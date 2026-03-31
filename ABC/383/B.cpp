#include <bits/stdc++.h>
using namespace std;

int main() {
  int H,W,D;cin>>H>>W>>D;
  vector<string> S(H);
  for(int i=0;i<H;i++)cin>>S[i];
  
  vector<int> x,y;
  for(int i=0;i<H;i++)for(int j=0;j<W;j++)if(S[i][j]=='.'){
    x.push_back(i);
    y.push_back(j);
  }
  
  int N=x.size();
  int ans=-1;
  
  for(int i=0;i<N-1;i++)for(int j=i+1;j<N;j++){//すべての位置に加湿器を設置する
    int cnt=0;
    for(int h=0;h<H;h++)for(int w=0;w<W;w++){
      if(S[h][w]=='.'&&((abs(x[i]-h)+abs(y[i]-w))<=D||(abs(x[j]-h)+abs(y[j]-w))<=D))cnt++;
    }
    
    ans=max(ans,cnt);
  }
  
  cout<<ans<<endl;
}
#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  vector<pair<double,double>> p(N+2);
  p[0].first=0;
  p[0].second=0;
  p[N+1].first=0;
  p[N+1].second=0;
  for(int i=1;i<=N;i++)cin>>p[i].first>>p[i].second;
  
  double ans=0;
  
  for(int i=1;i<=N+1;i++){
    ans+=sqrt((p[i].first-p[i-1].first)*(p[i].first-p[i-1].first)+(p[i].second-p[i-1].second)*(p[i].second-p[i-1].second));
  }
  
  printf("%.10f\n",ans);
}
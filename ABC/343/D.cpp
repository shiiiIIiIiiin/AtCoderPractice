#include <bits/stdc++.h>
using namespace std;

int main() {
  int N,T;
  cin>>N>>T;
  map<long long int,int> C;//（添え字）点の選手の人数を保持するマップ
  long long int P[N+1];//各選手の得点
  for(int i=1;i<=N;i++)P[i]=0;
  
  C[0]=N;
  
  for(int i=1;i<=T;i++){
    int a,b;
    cin>>a>>b;
    if(--C[P[a]]==0)C.erase(P[a]);
    C[P[a]+b]++;
    P[a]+=b;
    cout<<C.size()<<endl;
  }
}

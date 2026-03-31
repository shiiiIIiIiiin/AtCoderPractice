#include <bits/stdc++.h>
using namespace std;

int main(){
  long long T;cin>>T;
  
  for(int i=0;i<T;i++){//O(T)かかる　solveはlogレベルで素早くしないといけない
    long long N,D,K;cin>>N>>D>>K;
    int a=N/gcd(N,D);
    cout<<(K-1)/a+D*(K-1)%N<<endl;
  }
  
}
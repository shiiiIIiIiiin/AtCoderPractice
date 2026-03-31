#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;cin>>N;
  cout<<(5-N%5<N%5 ? N+5-N%5:N-N%5)<<endl;
}
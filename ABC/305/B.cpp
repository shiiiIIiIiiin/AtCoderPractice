#include <bits/stdc++.h>
using namespace std;

int main() {
  int a[]={0,3,1,4,1,5,9};
  for(int i=1;i<7;i++)a[i]+=a[i-1];
  char p,q;cin>>p>>q;
  cout<<abs(a[p-'A']-a[q-'A'])<<endl;
}
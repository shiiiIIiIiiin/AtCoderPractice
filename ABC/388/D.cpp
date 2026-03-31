#include<bits/stdc++.h>
#include<atcoder/all>
using namespace atcoder;
using namespace std;
using ll=long long;

int main(){
  int N;cin>>N;
  vector<int> A(N);
  for(int i=0;i<N;i++)cin>>A[i];
  
  //あげられなくなるかを判定する
  
  multiset<ll> st;
  ll ashikiri=0;
  
  for(int i=0;i<N;i++){//成人した瞬間にいくつになるか考える
    A[i]+=st.size();//払える人全員からもらう
    st.insert(A[i]+i);
    
    
    //stから払えなくなる人を抜く
    auto it=st.lower_bound(i+1);
    st.erase(st.begin(),it);
  }
  
  for(int i=0;i<N;i++)cout<<max(0,A[i]-(N-1-i))<<" ";
}
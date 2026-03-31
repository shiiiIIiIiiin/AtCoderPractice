#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;
#define rng(i,a,b) for(int i=int(a);i<int(b);i++)
#define rep(i,b) rng(i,0,b)
#define all(p) p.begin(),p.end()
#define fi first
#define se second
#define pb push_back
using ull=unsigned long long;using ll=long long;using vi=vector<int>;using pii=pair<int,int>;
using pll=pair<ll,ll>;using vpii=vector<pii>;using vs=vector<string>;using vl=vector<ll>;
using vb=vector<bool>;using vvb=vector<vb>;using vvi=vector<vi>;using vvl=vector<vl>;
const int mod1=998244353;const int mod2=1000000007;

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    //cout<<fixed<<setprecision(15);atcoder::mint::set_mod(mod1);

    int n,k;cin>>n>>k;
    int mk=0,len=0;
    string s;cin>>s;
    vector<char>t(n+2);
    t[0]='.';t[n+1]='.';
    rep(i,n)t[i+1]=s[i];
    rng(i,1,n+1){
      if(t[i]=='o')mk++;
      if(t[i]=='o' && t[i-1]=='?')t[i-1]='.';
      if(t[i]=='o' && t[i+1]=='?')t[i+1]='.';
    }
    if(mk==k){
      rep(i,n){
        if(t[i+1]=='?')t[i+1]='.';
      }
      rng(i,1,n+1)cout<<t[i];
      return 0;
    }
    vi a;
    rep(i,n+1){
        if(t[i+1]=='?')len++;
        if(t[i+1]=='.' && len){
            if(len%2){
                mk+=(len+1)/2;
                a.pb(i);
            }else mk+=len/2;
            len=0;
        }
    }
    if(mk==k){
        for(auto v:a){
            int ii=v;
            bool b=true;
            while(ii>=0){
                if(t[ii]=='.')break;
                if(b){
                    t[ii]='o';
                    b=false;
                }else{
                    t[ii]='.';
                    b=true;
                }
                ii--;
            }
        }
    }
    rng(i,1,n+1)cout<<t[i];
    return 0;
}
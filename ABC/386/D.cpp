#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
    ll N,M;
    cin>>N>>M;
    vector<ll> x_coords,y_coords;
    vector<tuple<ll,ll,char>> input;
    
    for(int i=0;i<M;i++){
        ll x,y;
        char c;
        cin>>x>>y>>c;
        x_coords.push_back(x);
        y_coords.push_back(y);
        input.emplace_back(x,y,c);
    }
    
    sort(x_coords.begin(),x_coords.end());
    x_coords.erase(unique(x_coords.begin(),x_coords.end()),x_coords.end());
    sort(y_coords.begin(),y_coords.end());
    y_coords.erase(unique(y_coords.begin(),y_coords.end()),y_coords.end());
    auto compress=[](ll val,const vector<ll>& coords){
        return lower_bound(coords.begin(),coords.end(),val)-coords.begin();
    };
    
    ll nx=x_coords.size(),ny=y_coords.size();
    vector<ll> tate(nx,-1),yoko(ny,-1);
    vector<tuple<ll,ll>> siro;
    for(auto [x,y,c]:input){
        ll cx=compress(x,x_coords);
        ll cy=compress(y,y_coords);
        if(c=='B'){
            tate[cx]=max(tate[cx],cy);
            yoko[cy]=max(yoko[cy],cx);
        }else{
            siro.emplace_back(cx,cy);
        }
    }
    for(int i=nx-1;i>=1;i--)tate[i-1]=max(tate[i-1],tate[i]);
    for(int i=ny-1;i>=1;i--)yoko[i-1]=max(yoko[i-1],yoko[i]);
    for(auto [cx,cy]:siro){
        if(cx<=yoko[cy]||cy<=tate[cx]){
            cout<<"No"<<endl;
            return 0;
        }
    }
    cout<<"Yes"<<endl;
    return 0;
}
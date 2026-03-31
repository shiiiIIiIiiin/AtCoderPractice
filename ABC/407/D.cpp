//#define _GLIBCXX_DEBUG

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <map>
#include <set>
#include <iterator>
#include <unordered_map>
#include <stack>
#include <string>
#include <cmath>
#include <iomanip>
#include <deque>
#include <unordered_set>

using namespace std;
using ll = long long;

const ll MOD = 998244353;
const ll MOD2 = 1'000'000'007;

class SegTree {
public:
	vector<ll> dat;
	ll siz = 1;

	SegTree(ll n) {
		while (siz < n)siz *= 2;
		dat.resize(2 * siz, -LLONG_MAX);
	}

	void update(int id, ll x) {
		id += siz;
		dat[id] = x;
		while (id != 0) {
			id /= 2;
			dat[id] = max(dat[2 * id], dat[2 * id + 1]);
		}
	}

	ll getval(int id) {
		return dat[id + siz];
	}

	ll getmax(ll L, ll R, ll a, ll b, ll u) {
		if (b <= L || R <= a)return -LLONG_MAX / 2;
		if (L <= a && b <= R)return dat[u];

		ll m = (a + b) / 2;

		return max(getmax(L, R, a, m, 2 * u), getmax(L, R, m, b, 2 * u + 1));
	}
};

class UnionFind {
public:
	vector<int> siz, par;

	UnionFind(int n) {
		siz.resize(n, 1);
		par.resize(n, -1);
	}

	int root(int x) {
		if (par[x] == -1) return x;
		return par[x] = root(par[x]);
	}

	void unite(int x, int y) {
		int rx = root(x), ry = root(y);
		if (rx == ry)return;

		if (siz[rx] < siz[ry]) {
			par[rx] = ry;
			siz[ry] += siz[rx];
		}
		else {
			par[ry] = rx;
			siz[rx] += siz[ry];
		}

	}

	bool same(int x, int y) {
		return root(x) == root(y);
	}

};

long long modinv(long long a, long long m) {//mod. m での a の逆元 a^{-1} を計算する
	long long b = m, u = 1, v = 0;
	while (b) {
		long long t = a / b;
		a -= t * b; swap(a, b);
		u -= t * v; swap(u, v);
	}
	u %= m;
	if (u < 0) u += m;
	return u;
}

long long modpow(long long a, long long n, long long mod) {// a^n mod を計算する
	long long res = 1;
	while (n > 0) {
		if (n & 1) res = res * a % mod;
		a = a * a % mod;
		n >>= 1;
	}
	return res;
}

int dx[] = { 1,0,-1,0 }, dy[] = { 0,1,0,-1 };

int  H,W;
int dx2[]={1,0},dy2[]={0,1};

void dfs(vector<bool>& can,vector<vector<ll>>& A,vector<vector<bool>>& used,ll pos){
	if(pos==H*W-1){
		ll memo=0;
		for(ll i=0;i<H;i++)for(ll j=0;j<W;j++)if(!used[i][j])memo|=(1LL<<(i*W+j));
		can[memo]=true;
		return;
	}

	dfs(can,A,used,pos+1);//何も置かない場合

	int h=pos/W,w=pos%W;

	if(used[h][w])return;

	for(int d=0;d<2;d++){
		int nx=h+dx2[d],ny=w+dy2[d];
		if(nx<0||H<=nx||ny<0||W<=ny)continue;
		if(used[nx][ny])continue;

		used[h][w]=true;
		used[nx][ny]=true;
		dfs(can,A,used,pos+1);
		used[h][w]=false;
		used[nx][ny]=false;
	}
}

int main() {
	cin >> H >> W;
	vector<vector<ll>> A(H,vector<ll>(W));
	for(int i=0;i<H;i++)for(int j=0;j<W;j++)cin>>A[i][j];

	vector<vector<bool>> used(H,vector<bool>(W,false));

	vector<bool> can(1LL<<(H*W)+1,false);
	can[0]=true;

	dfs(can,A,used,0LL);

	ll ans=-1;

	for(ll i=0;i<(1LL<<(H*W));i++){
		if(!can[i])continue;

		ll memo=0;

		for(ll j=0;j<H*W;j++){
			//if((i & (1<<j))==0) memo^=A[j/W][j%W];
			if((i>>j)&1==1) memo^=A[j/W][j%W];
			
		}
		ans=max(ans,memo);
	}

	cout<<ans<<endl;
}
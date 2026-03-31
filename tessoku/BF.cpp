#include<iostream>
#include<vector>
#include<queue>
#include<climits>
#include<algorithm>
#include<map>
#include<set>
using namespace std;
using ll = long long;

class segtree {
public:
	vector<ll> dat;
	ll siz = 1;//配列事態の大きさ、全体の大きさは2*siz-1

	segtree(ll n) {
		while (siz < n)siz *= 2;
		dat.resize(2*siz,0);
	}

	void update(ll id, ll x) {
		id += siz;
		dat[id] = x;
		while (id >= 1) {
			id /= 2;
			dat[id] = max(dat[2 * id], dat[2 * id + 1]);
		}

	}

	ll getmax(ll l, ll r, ll a, ll b, ll pos) {
		if (b <= l || r <= a)return -LLONG_MAX;
		if (l <= a && b <= r)return dat[pos];

		ll m = (a + b) / 2;
		
		return max(getmax(l, r, a, m, 2 * pos), getmax(l, r, m, b, 2 * pos + 1));
	}

	ll getid() {
		ll res = 1;

		while (!(siz <= res && res <= 2 * siz)) {
			res = 2 * res + (dat[2 * res] < dat[2 * res + 1] ? 0 : 1);
		}

		return res-siz;
	}


};

int main() {
	ll N, Q; cin >> N >> Q;
	segtree sg(N);

	for(int i=0;i<Q;i++){
		int type; cin >> type;

		if (type == 1) {
			ll pos, x; cin >> pos >> x;
			sg.update(pos - 1, x);
		}
		else {
			ll l, r; cin >> l >> r;
			cout << sg.getmax(l-1, r-1, 0, sg.siz, 1) << endl;
		}
	}

	//for(int i=0;i<N;i++)cout<<sg.dat[sg.siz+i]<<" ";
	
}
#include<iostream>
#include<vector>
#include<queue>
#include<climits>
#include<algorithm>
#include<map>
#include<set>
using namespace std;
using ll = long long;


ll cnt(set<ll>& s, ll pos, ll dx, map<ll,set<ll>> &t,ll k) {

	ll l, r;
	l = min(pos, pos + dx), r = max(pos, pos + dx);

	auto itl = s.lower_bound(l), itr = s.upper_bound(r);
	ll res = distance(itl,itr);

	while (itl != itr) {
		auto nex = next(itl);

		t[*itl].erase(k);
		s.erase(itl);
		itl=nex;
	}

	//s.erase(itl, itr);

	return res;
}


int main() {
	ll N, M, posx, posy; cin >> N >> M >> posx >> posy;
	map<ll,set<ll>> tate, yoko;

	for (int i = 0; i < N; i++) {
		ll x, y; cin >> x >> y;
		tate[x].insert(y);
		yoko[y].insert(x);
	}

	ll ans = 0;

	for (int i = 0; i < M; i++) {
		char d;
		ll c;
		cin >> d >> c;

		if (d == 'U') {
			ans += cnt(tate[posx], posy, c, yoko, posx);
			posy += c;
		}
		else if (d == 'D') {
			ans += cnt(tate[posx], posy, -c, yoko, posx);
			posy -= c;
		}
		else if (d == 'L') {
			ans += cnt(yoko[posy], posx, -c, tate, posy);
			posx -= c;

		}
		else {
			ans += cnt(yoko[posy], posx, c, tate, posy);
			posx += c;
		}

	}

	cout << posx << " " << posy << " " << ans << endl;

}
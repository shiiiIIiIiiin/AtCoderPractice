#include<iostream>
#include<vector>
#include<queue>
#include<climits>
#include<algorithm>
#include<map>
#include<set>
using namespace std;
using ll = long long;

ll to_10(string& s) {
	ll res = 0;

	for (int i = 0; i < s.size(); i++) {
		res *= 8;
		res += s[i] - '0';
	}

	//cout << res << endl;

	return res;
}

string to_9(ll x) {
	string res = "";

	while (x != 0) {
		res += char(x % 9 + '0');
		x /= 9;
	}

	reverse(res.begin(), res.end());

	//cout << res << endl;

	return res;
}



int main() {
	string S;
	ll K; cin >> S >> K;

	if (S == "0") {
		cout << 0 << endl;
		return 0;
	}

	for (int i = 0; i < K; i++) {
		ll t = to_10(S);//Sを10進法のtに直す
		string u = to_9(t);//tを9進法に直す

		for (int j = 0; j < u.size(); j++)if (u[j] == '8')u[j] = '5';
		S = u;
	}

	cout << S << endl;

}
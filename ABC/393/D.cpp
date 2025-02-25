#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <map>
#include <set>
#include <iterator>

using namespace std;
using ll = long long;

int main() {
	ll N; cin >> N;
	string S; cin >> S;
	vector<int> memo;
	for (int i = 0; i < N; i++)if (S[i] == '1')memo.push_back(i);

	ll ans = 100000000000;

	ll M = memo.size();
	
	if(M==0){
	  cout<<'0'<<endl;
	  return 0;
	}
	
	if(M==1){
	  cout<<'0'<<endl;
	  return 0;
	}
	
	if(M==2){
	  cout<<llabs(memo[1]-memo[0])-1<<endl;
	  return 0;
	}

	ll cnt = 0;
	for (ll i = 0; i < M; i++) {
		if (M / 2 != i)cnt += llabs(memo[M / 2] - memo[i]) - llabs(M / 2 - i);
	}

	ans = min(ans, cnt);


	cnt = 0;
	for (ll i = 0; i < M; i++) {
		if (M / 2 + 1 != i)cnt += llabs(memo[M / 2 + 1] - memo[i]) - llabs(M / 2 + 1 - i);
	}

	ans = min(ans, cnt);

	cout << ans << endl;
}

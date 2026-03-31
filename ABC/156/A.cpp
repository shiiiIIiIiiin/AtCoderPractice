#include<iostream>
#include<vector>
#include<queue>
#include<climits>
#include<algorithm>
#include<map>
#include<set>
using namespace std;
using ll = long long;

int main() {
	int N, R; cin >> N >> R;

	cout << R + max(0, 10 - N) * 100 << endl;
}
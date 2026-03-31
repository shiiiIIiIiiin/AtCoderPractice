#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <map>
#include <set>
#include <iterator>
#include <unordered_map>

using namespace std;
using ll = long long;

const int MAX_A = 1000000;

int main() {
	//強さ（A）が小さくてコスト（C）が高いカードのペアがあれば捨てる
	int N; cin >> N;
	vector<tuple<int, int, int>> card;
	for (int i = 0; i < N; i++) {
		int a, c;cin >> a >> c;
		card.push_back({ a, c, i + 1 });
	}

	sort(card.begin(), card.end());
	reverse(card.begin(), card.end());//強さが強い順になってるはず、cは昇順に並んでないといけない

	set<int> memo;//捨てるカードのインデックスを保持
	int cnt = 1000000000;

	for (int i = 0; i < N; i++) {
		int c = get<1>(card[i]);
		if (c > cnt)memo.insert(i);//前のやつのほうが強いかつ今見たやつのほうがコストが大きい
		cnt = min(cnt, c);
	}

	vector<int> ans;

	for (int i = 0; i < N; i++)if (!memo.count(i))ans.push_back(get<2>(card[i]));
	sort(ans.begin(), ans.end());
	cout << ans.size() << endl;
	for (auto x : ans)cout << x << " ";
}
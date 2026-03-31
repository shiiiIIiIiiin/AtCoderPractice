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
#include <locale>
#include <random>


using namespace std;
using ll = long long;

const ll INF = LLONG_MAX / 2;

long long modpow(long long a, long long n, long long mod) {
	long long res = 1;
	while (n > 0) {
		if (n & 1) res = res * a % mod;
		a = a * a % mod;
		n >>= 1;
	}
	return res;
}

int main() {
	ll N, M, L, U; cin >> N >> M >> L >> U;
	vector<ll> A(N);

	for (int i = 0; i < M; i++) {
		A[i] = L + max(0LL, ((i - 2) * (U - L)) / M);//主力カードは階段状に初期化する
		cout << A[i] << " ";
	}
	

	vector<int> cnt(40, 0);
	int cnt_idx = M;
	// 2^39を10枚
	for (int i = 0; i < 10; i++) {
		A[cnt_idx++] = 1LL << 39;
		cnt[39]++;
		cout<<(1LL<<39)<<" ";
	}

	// 2^38, 2^37... と27枚ずつ、カードがなくなるまで生成
	int k = 38;
	while (cnt_idx < N) {
		for (int i = 0; i < 27; ++i) {
			if (cnt_idx < N){
			  A[cnt_idx++] = 1LL << k;
			  cout<<(1LL<<k)<<" ";
			}
			cnt[k]++;
		}
		k--;
	}
	cout<<endl;
	

	vector<ll> B(M);
	for (int i = 0; i < M; i++)cin >> B[i];

	vector<int> assignment(N, 0); // カードiの所属山 (0=捨て)

	// Step 1: 主力カードをまず割り当てる
	for (int i = 0; i < M; i++) {
		assignment[i] = i + 1;
	}

	// Step 2: 各山の「埋めるべき差額」を計算する
	vector<pair<ll, int>> diffs(M);
	for (int i = 0; i < M; i++) {
		diffs[i] = { B[i] - A[i], i }; // {差額, 元の山のインデックス}
	}
	// 差額が大きい山から優先して処理するためにソート
	sort(diffs.rbegin(), diffs.rend());

	// Step 3: 調整用カードを手持ちのプールに入れる
	vector<pair<ll, int>> adjust_cards;
	for (int i = M; i < N; i++) {
		adjust_cards.push_back({ A[i], i });
	}
	// 大きいカードから使えるようにソートしておく
	sort(adjust_cards.rbegin(), adjust_cards.rend());

	vector<bool> card_is_used(N, false);
	for (int i = 0; i < M; ++i) card_is_used[i] = true;

	// Step 4: 差額が大きい山から順に、最適なカードで埋めていく
	for (const auto& p : diffs) {
		ll remaining_diff = p.first;
		int group_idx = p.second;

		// 差額がマイナス（既に超過）の場合は何もしない
		if (remaining_diff <= 0) continue;

		// 手持ちの大きい調整用カードから見ていき、差額を超えない最大のものを貪欲に選んでいく
		for (const auto& card_info : adjust_cards) {
			ll card_val = card_info.first;
			int card_original_idx = card_info.second;

			// まだ使われていないカードで、かつ差額を超えないものを探す
			if (!card_is_used[card_original_idx] && remaining_diff >= card_val) {
				// 見つけたら、そのカードをこの山に割り当てる
				assignment[card_original_idx] = group_idx + 1;
				remaining_diff -= card_val; // 残りの差額を更新
				card_is_used[card_original_idx] = true; // このカードは使用済み
			}
		}
	}

	// --- 最終結果の出力 ---
	for (int i = 0; i < N; i++) {
		cout << assignment[i] << " ";
	}cout << endl;
	

}
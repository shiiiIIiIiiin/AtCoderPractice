#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  int N, K; cin >> N >> K;
  vector<vector<ll>> cards(4, vector<ll>(N));
  for (int i = 0; i < 4; i++)for (int j = 0; j < N; j++)cin >> cards[i][j];

  vector<ll> cnt;
  set<ll> st;

  for (int i = 0; i < N; i++)for (int j = 0; j < N; j++) {
    st.insert(cards[0][i] + cards[1][j]);
    cnt.push_back(cards[2][i] + cards[3][j]);
  }


  for (int i = 0; i < cnt.size(); i++) {
    ll target = K - cnt[i];
    if (st.count(target)) {
      cout << "Yes";
      return 0;
    }
  }

  cout << "No";
}
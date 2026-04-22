#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using ll = long long;

int main() {
  int N, K; cin >> N >> K;
  vector<ll> a(N + 1, 1);
  a[0] = 0;
  auto a2 = convolution(a, a);
  auto a3 = convolution(a2, a);

  cout << (a3.size() > K ? a3[K] : 0) << endl;
}
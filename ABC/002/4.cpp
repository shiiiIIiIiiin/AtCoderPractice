#include<bits/stdc++.h>
using namespace std;

int main(){
  int N, M;
  cin >> N >> M;
  vector<vector<bool>> siriai(N + 1, vector<bool> (N + 1, false));
  
  for(int i = 0; i < M; i++){
    int x, y;
    cin >> x >> y;
    siriai[x][y] = true;
    siriai[y][x] = true;
  }
  
  int ans = 0;  // 最小値は0でよい（無効な部分集合を扱うため）

  for(int i = 0; i < 1 << N; i++){
    vector<int> member;
    
    // ビットマスクによる部分集合の作成
    for(int cnt = 0; cnt < N; cnt++){
      if(i & (1 << cnt)) member.push_back(cnt + 1);
    }
    
    // 空の部分集合をスキップ
    if (member.empty()) continue;

    bool valid = true;

    // 部分集合内の友好関係を確認
    for (int j = 0; j < member.size() - 1 && valid; j++) {
      for (int k = j + 1; k < member.size(); k++) {
        if (!siriai[member[j]][member[k]]) {
          valid = false;
          break;  // 友好関係がない場合はスキップ
        }
      }
    }

    // 有効な部分集合の場合、サイズを評価
    if (valid) {
      ans = max(ans, (int)member.size());
    }
  }
  
  cout << ans << endl;
}
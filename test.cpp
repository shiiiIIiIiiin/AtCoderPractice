/*
（注）
・オーバーフロー対策をしていません
・計算量はO(2^N)なのでNが小さくないと時間がかかります

-----
軽い解説
　・再帰関数を用いた全探索です.（計算量を気にしなければ）とても多くの問題をこの方法で解くことができます.

　・関数checkについて
　　　check(idx,target)を以下のように定義します
　　　　(i)idx==Nの場合
　　　　　　target が 0 と等しい場合は true, そうでない場合 false を返す

　　　　(ii)それ以外の場合
           check(idx+1,target) か check(idx+1,taeget-A[idx]) のどちらかが true だったら true, それ以外は false を返す

　・求める答えは check(0,K) が true か false かによって判定できます.
　・　↑　これがなんでそうなるのかが分かればこの問題は理解したと言えると思います. もし分からなければAIに聞くととても分かりやすく教えてくれます.
　・が、僕からも少し説明すると　「A[idx]を加えた未来」と「A[idx]を加えなかった未来」のどちらかで成功すれば、元の問題も成功する、というイメージです. 
*/

#include <bits/stdc++.h>
using namespace std;

int N, K;
int A[22];

bool check(int idx, int target) {
    if (idx == N)return target == 0;
    return check(idx + 1, target) || check(idx + 1, target - A[idx]);
}

int main() {
    //入力を受け取る
    cin >> N >> K;
    for (int i = 0; i < N; i++) cin >> A[i];

    //答えを出力する
    if (check(0, K))cout << "Yes";
    else cout << "No";
}
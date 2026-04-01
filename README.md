# AtCoderPractice
AtCoderの回答をまとめたものです

## コンテストフォルダの作成

`~/.bashrc` に `new_contest` 関数が登録されているので、Git Bash からどこでも使える。

```bash
new_contest 401
# または
new_contest ABC401
```

`AtCoderPractice/ABC/401/` が作成され、`sample.cpp` をコピーした `A.cpp` 〜 `G.cpp` が生成される。

### サンプル取得・テスト

```bash
# コンテスト開始時
new_contest 403          # フォルダ作成 + A〜G のサンプルを自動取得
cd AtCoderPractice/ABC/403

# 実装したら
t a                      # A.cpp をコンパイルしてテスト実行（大文字小文字どちらでもOK）
```

サンプルは `test_a/`, `test_b/`, ... に保存される。手動で再取得したい場合：

```bash
dl 403 a       # abc403_a のサンプルを取得
```

### 問題ファイルを開く

```bash
op ABC 451 F    # ABC/451/ に移動して F.cpp を開く
op abc 451 f    # 大文字小文字どちらでもOK
op ABC 451      # 移動だけ（ファイルは開かない）
```

`F.cpp` が存在しない場合は `sample.cpp` からテンプレートをコピーして作成する。

---

## コンパイル方法

リポジトリルート(`AtCoderPractice/`)から実行する場合：
```bash
g++ -std=gnu++2b -I vendor/ac-library <ソースファイル.cpp> -o <出力ファイル>
```

問題ディレクトリ（例: `ABC/446/`）から実行する場合：
```bash
g++ -std=gnu++2b -I ../../vendor/ac-library <ソースファイル.cpp> -o <出力ファイル>
```

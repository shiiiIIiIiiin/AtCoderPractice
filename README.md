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
dl 403         # abc403 の A〜G 全問のサンプルを取得
dl 403 a       # abc403_a のサンプルのみ取得
```

### 問題ファイルを開く

```bash
op ABC 451 F    # ABC/451/ に移動して F.cpp を開く
op abc 451 f    # 大文字小文字どちらでもOK
op ABC 451      # 移動だけ（ファイルは開かない）
```

`F.cpp` が存在しない場合は `sample.cpp` からテンプレートをコピーして作成する。

---

## AHCコンテストのセットアップ

`~/.bashrc` に `new_ahc` 関数が登録されているので、Git Bash からどこでも使える。

```bash
new_ahc 056
# または
new_ahc ahc056
```

`AtCoderPractice/AHC/AHC056/` が作成され、以下の構成で自動生成される：

```
AHC056/
├── problem/
│   ├── statement.md   # 問題文（ビジュアライザURLリンク付き）
│   └── images/        # 手動スクショを置く場所
├── tools/             # vis.exe, gen.exe, in/, seeds.txt
└── main.cpp           # 自分で作成（ルートに置く運用）
```

### ビジュアライザの使い方

```bash
cd AtCoderPractice/AHC/AHC056

# テストケース生成
./tools/gen.exe 0 > input.txt

# 自分の解法を実行
./main.exe < input.txt > output.txt

# ビジュアライズ → vis.html が生成される
./tools/vis.exe input.txt output.txt
```

Web版ビジュアライザのURLは `問題文.md` の「ツール」セクションに記載されている。

### 依存パッケージ（初回のみ）

```bash
pip install requests beautifulsoup4
```

スクリプト本体: `scripts/fetch_ahc.py`

---

## ojのログイン設定（コンテスト中のサンプル取得に必要）

コンテスト中の問題はログインが必要。`oj login` はCloudflareに弾かれるため、クッキーを手動で設定する。

### 手順

1. ブラウザでAtCoderにログイン
2. F12 → Application → Cookies → `https://atcoder.jp`
3. `REVEL_SESSION` の Value をコピー
4. Git Bash で以下を実行（`<値>` を置き換える）：

```bash
python3 - << 'EOF'
import http.cookiejar, time, os

path = os.path.expandvars(r"C:\Users\kimura\AppData\Local\online-judge-tools\online-judge-tools\cookie.jar")
jar = http.cookiejar.LWPCookieJar(path)

cookie = http.cookiejar.Cookie(
    version=0, name="REVEL_SESSION", value="<値>",
    port=None, port_specified=False,
    domain=".atcoder.jp", domain_specified=True, domain_initial_dot=True,
    path="/", path_specified=True,
    secure=False, expires=int(time.time()) + 60*60*24*30,
    discard=False, comment=None, comment_url=None, rest={}
)
jar.set_cookie(cookie)
jar.save(ignore_discard=True, ignore_expires=True)
print("Done")
EOF
```

5. 確認：

```bash
oj login --check https://atcoder.jp/
# → [SUCCESS] You have already signed in. が出ればOK
```

クッキーの有効期限は数週間〜数ヶ月。切れたら同じ手順で更新する。

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

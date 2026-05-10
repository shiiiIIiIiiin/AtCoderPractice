# AtCoderPractice

AtCoderの回答をまとめたリポジトリ。

## クイックリファレンス

| コマンド | 説明 |
|---|---|
| `new_contest ABC401` | フォルダ作成 + サンプル取得 |
| `dl ARC190 a` | サンプル手動取得 |
| `dl TESSOKU 50` | 問題集を番号で取得 |
| `c a` | A.cpp をコンパイル |
| `t a` | A.cpp をコンパイル + テスト実行 |
| `op ABC 451 F` | フォルダ移動 + F.cpp を開く |
| `new_ahc 056` | AHCセットアップ |

---

## new_contest — フォルダ作成

`~/.bashrc` に登録済み。Git Bash からどこでも使える。

### 通常コンテスト

```bash
new_contest ABC401    # ABC/401/ を作成、A〜G のサンプルを自動取得
new_contest ARC190    # ARC/190/ を作成、A〜F のサンプルを自動取得
new_contest AGC070    # AGC/070/ を作成、A〜F のサンプルを自動取得
new_contest AWC13     # AWC/13/  を作成、A〜E のサンプルを自動取得（URL は awc0013）
new_contest 401       # 数字のみは ABC 扱い → ABC/401/
```

実行後、自動的に作成したフォルダに移動する。

### 問題集（テンプレートのみ作成、サンプルは dl で都度取得）

```bash
new_contest EDPC       # EDPC/     A〜Z  (26問)
new_contest FPS        # FPS/      A〜X  (24問)
new_contest TESSOKU    # TESSOKU/  A〜FR (174問)
new_contest TYPICAL90  # TYPICAL90/ A〜CL (90問)
```

---

## dl — サンプル取得（手動）

### 通常コンテスト

```bash
dl 401          # ABC401 の A〜G 全問
dl 401 a        # ABC401 の A のみ
dl ARC190       # ARC190 の A〜F 全問
dl ARC190 a     # ARC190 の A のみ
dl AWC13        # AWC0013 の A〜E 全問
```

### 問題集（番号指定 / 全問）

```bash
dl EDPC         # EDPC 全26問をダウンロード
dl EDPC 12      # EDPC 12問目のみ → test/l/ に保存
dl TESSOKU 50   # 鉄則 50問目のみ → test/ax/ に保存
dl TYPICAL90 45 # 典型90 45問目のみ → test/cl/ に保存
dl FPS 10       # FPS 10問目のみ → test/j/ に保存
```

問題番号 → フォルダ名の対応: 1=a, 2=b, ..., 26=z, 27=aa, 28=ab, ...

### URL 直接指定（鉄則の一部など非標準URL問題用）

```bash
dl URL https://atcoder.jp/contests/tessoku-book/tasks/math_and_algorithm_o
```

---

## c — コンパイルのみ

```bash
c a    # A.cpp をコンパイル → a.out
c L    # L.cpp をコンパイル → a.out（大文字小文字どちらでもOK）
```

---

## t — コンパイル + テスト実行

```bash
t a    # A.cpp をコンパイルして test/a/ のサンプルでテスト
t L    # L.cpp をコンパイルして test/l/ のサンプルでテスト
```

問題集の場合はラベルで指定する（例: EDPC 12問目 → `t l`）。

---

## op — フォルダ移動 + ファイルを開く

```bash
op ABC 451 F    # ABC/451/ に移動して F.cpp を VSCode で開く
op abc 451 f    # 大文字小文字どちらでもOK
op ABC 451      # 移動のみ（ファイルは開かない）
```

`F.cpp` が存在しない場合は `sample.cpp` からテンプレートをコピーして作成する。

---

## new_ahc — AHC セットアップ

```bash
new_ahc 056
new_ahc ahc056   # どちらでも同じ
```

`AHC/AHC056/` が作成され、問題文（Markdown）が自動取得される。

```
AHC056/
├── problem/
│   ├── statement.md   # 問題文（ビジュアライザURLリンク付き）
│   └── images/        # 手動スクショを置く場所
└── tools/             # vis.exe, gen.exe, in/, seeds.txt
```

### ビジュアライザの使い方

```bash
cd AHC/AHC056
./tools/gen.exe 0 > input.txt
./main.exe < input.txt > output.txt
./tools/vis.exe input.txt output.txt    # vis.html が生成される
```

Web 版ビジュアライザの URL は `problem/statement.md` に記載されている。

### 初回のみ

```bash
pip install requests beautifulsoup4
```

---

## oj ログイン設定

コンテスト中の問題はログインが必要。`oj login` は Cloudflare に弾かれるため、クッキーを手動で設定する。

1. ブラウザで AtCoder にログイン
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

## 手動コンパイル

```bash
# 問題ディレクトリ（例: ABC/401/）から
g++ -std=gnu++2b -I ../../vendor/ac-library A.cpp -o a.out

# リポジトリルートから
g++ -std=gnu++2b -I vendor/ac-library ABC/401/A.cpp -o a.out
```

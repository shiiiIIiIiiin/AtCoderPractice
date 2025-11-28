AtCoder ライブラリ (ACL) ヘルパー

このリポジトリには AtCoder Library がサブモジュールとして `vendor/ac-library` に含まれています。

使い方（簡潔）

- 単一のソースファイルをビルドする（bash）:
  ./scripts/compile.sh path/to/file.cpp

- 単一のソースファイルをビルドする（PowerShell）:
  ./scripts/compile.ps1 path\to\file.cpp

両方のスクリプトは `vendor/ac-library` をインクルードパスに追加します。手動でコンパイルすることもできます:

g++ -std=c++17 -O2 -I vendor/ac-library -o path/to/output.exe path/to/file.cpp

注意事項:

- このリポジトリをクローンしたら、サブモジュールを初期化してください:
  git submodule update --init --recursive
- `#include <atcoder/all>` または `#include <atcoder/dsu.hpp>` のように個別のヘッダを使ってください。

-- ローカル g++ ラッパー (便利な使い方)

毎回 `-I vendor/ac-library` を書くのが面倒な場合、リポジトリに用意したローカルラッパーを使えます。

- tools/bin/g++ を PATH に追加すると、普段の `g++ A.cpp` のようなコマンドで自動的に `vendor/ac-library` を include します。

bash (一時的に PATH に追加):

```bash
export PATH="$PWD/tools/bin:$PATH"
g++ ABC/ACLPC/A.cpp -o ABC/ACLPC/A.exe
```

PowerShell (一時的に PATH に追加):

```powershell
$env:Path = (Resolve-Path .\tools\bin).Path + ";" + $env:Path
g++ ABC\ACLPC\A.cpp -o ABC\ACLPC\A.exe
```

このラッパーは、既に `-I` オプションで `vendor/ac-library` を指定している場合は二重指定しません。

# AHC064 問題文

## ツール

- [Web ビジュアライザ](https://img.atcoder.jp/ahc064/fLqO0Ras.html?lang=ja)

- [Windows バイナリ](https://img.atcoder.jp/ahc064/fLqO0Ras_windows.zip)

×

In this contest, the following rules apply regarding the use of generative AI.

<a href="https://info.atcoder.jp/entry/ahc-llm-rules-en" target="_blank" rel="noopener" class="alert-link">AtCoder Heuristic Contest Generative AI Usage Rules - Version 20250616</a>

For details, please see <a href="https://atcoder.jp/posts/1495" target="_blank" rel="noopener" class="alert-link">this post</a>.

$(function() {
			$(".marked_warn_text").each(function() {
				$(this).html(marked($(this).text()));
			});
		})

### ストーリー

AtCoder国の高橋鉄道から、あなたに緊急の依頼が届いた。翌朝の一斉出発に向けて、貨物ターミナルでの車両の並べ替えを手伝ってほしいというのだ。

貨物ターミナルには、列車が出発するための線路（出発線）が複数並んでおり、車両が配置されている。
また、各出発線の末尾側には、車両を一時的に移しておくための線路（待避線）が同数設けられている。
出発線と待避線の間で車両を適切に移動させることで、各出発線に車両を所定の順序で並べたい。

ただし、複数の移動を同時に行う際、出発線と待避線を結ぶ経路どうしが交差すると、車両同士が互いの進路を塞いでしまう。そのため、同じタイミングに行う移動は、経路が互いに交差しないように選ぶ必要がある。

高橋鉄道のために、できるだけ少ない手順で、全ての車両を所定の順序に並べてほしい。

### 問題文

貨物ターミナルには R 本の出発線が並んでおり、出発線の出口とは反対側に R 本の待避線が配置されている。
出発線および待避線には、それぞれ左から右へ順に 0,1,\ldots,R-1 の番号が付けられている。
以降、出発線については出口側を「先頭」、その反対側を「末尾」と呼ぶ。待避線については、出発線に近い側を「先頭」、その反対側を「末尾」と呼ぶ。

任意の出発線と任意の待避線の間は線路でつながっており、車両は出発線と待避線の間を移動できる。
出発線は各線 15 両、待避線は各線 20 両の容量を持ち、この容量を超えるような移動は禁止されている。

初期状態では、各出発線に 10 両ずつ車両が配置されている。
各車両には 0,\ldots,10R-1 の ID が 1 つずつ振られており、出発線 r の先頭から c 両目に配置されている車両の ID は Y_{r,c} である。待避線はすべて空である。
出発線と待避線の間で車両を移動させることによって、各出発線 r について、ID 10r, 10r+1, \ldots, 10r+9 の車両を先頭から順に並べることが目標である。

各ターンでは、以下の 2 種類の移動を 複数同時に 行うことができる。各移動は連続した k 両（ k \ge 1 ）を対象とし、その順序は保存される。

- （type = 0）出発線 i の末尾から連続する k 両を取り出し、待避線 j の先頭に連結する。- （type = 1）待避線 j の先頭から連続する k 両を取り出し、出発線 i の末尾に連結する。

ただし、列車運行を安全に行うために、同一ターン内に行う移動は、移動方向を問わず、経路が互いに交差しないように選ばなければならない。すなわち、以下の 2 条件を満たさなければならない。

- 1 本の出発線または待避線を、同じターン内で 2 回以上使用してはならない。- 出発線 i_1 と待避線 j_1 の間での移動、出発線 i_2 と待避線 j_2 の間での移動を同時に行う場合、 i_1 < i_2 ならば j_1 < j_2 でなければならない。

移動は最大 4000 ターン行うことができる。

### 得点

出力した操作列のターン数を T とする。

すべての出発線が目標配置と完全に一致している場合、 100R + 4000 - T のスコアが得られる。

そうでない場合、最終状態の各出発線に配置された各車両（最大 10R 両）それぞれについて、以下の得点の総和がスコアとして得られる。

- 正しい出発線に配置されている場合：1 点- 先頭からの位置も正しい場合：追加で 9 点

ただし、ターン数が 4000 を超えた場合、または交差の制約もしくは各線の容量の制約に違反した場合は WA となる。

合計で 150 個のテストケースがあり、各テストケースの得点の合計が提出の得点となる。
一つ以上のテストケースで不正な出力や制限時間超過をした場合、提出全体の判定が WA や TLE となる。
コンテスト時間中に得た最高得点で最終順位が決定され、コンテスト終了後のシステムテストは行われない。 同じ得点を複数の参加者が得た場合、提出時刻に関わらず同じ順位となる。

### 入力

入力は以下の形式で標準入力から与えられる。

```
R
Y_{0,0} \cdots Y_{0,9}
\vdots
Y_{R-1,0} \cdots Y_{R-1,9}
```

- すべてのテストケースで、 R = 10 である。- Y_{r,c} は、初期状態において出発線 r の先頭から c 両目（ 0 \leq c < 10 ）に配置されている車両の ID である。- Y_{r,c} は 0,\ldots,10R-1 をちょうど 1 回ずつ含む。

### 出力

操作列を以下の形式で標準出力に出力せよ。

```
T
K_0
\mathrm{type} i j k
\vdots
\mathrm{type} i j k
\vdots
K_{T-1}
\mathrm{type} i j k
\vdots
\mathrm{type} i j k
```

ここで、 T は操作を行うターン数（ T \leq 4000 ）である。 T を出力した後、各ターン t = 0, 1, \cdots, T-1 について、以下をこの順に出力する。

- まず、そのターンで実行する移動数 K_t を 1 行で出力する（ 1 \leq K_t \leq R ）。- 続く K_t 行に、そのターンで実行する各移動を type i j k の形式（ \mathrm{type} \in \{0,1\} , 0 \leq i,j < R , k \geq 1 ）で出力する。 \mathrm{type} = 0 のとき、出発線 i の末尾から k 両を取り出し、待避線 j の先頭に連結する。 \mathrm{type} = 1 のとき、待避線 j の先頭から k 両を取り出し、出発線 i の末尾に連結する。

例を見る

### 入力生成方法

すべてのテストケースにおいて、 R = 10 である。

整数列 0,1,\ldots,10R-1 を一様ランダムに並び替え、並び替えた列を順に Y_{0,0}, Y_{0,1}, \ldots, Y_{0,9}, Y_{1,0}, \ldots, Y_{R-1,9} とする。

### ツール(入力ジェネレータ・ビジュアライザ)
- Web版 : ローカル版より高性能でアニメーション表示が可能です。- ローカル版 : 使用するには Rust言語 のコンパイル環境をご用意下さい。 Windows用のコンパイル済みバイナリ : Rust言語の環境構築が面倒な方は代わりにこちらをご利用下さい。

コンテスト期間中に、ビジュアライズ結果の共有や、解法・考察に関する言及は禁止されています。ご注意下さい。

### Story

An urgent request has arrived from Takahashi Railway in the AtCoder Kingdom. They want your help rearranging the railcars in the freight terminal for the simultaneous departures the next morning.

In the freight terminal, several tracks for departing trains (departure tracks) are lined up, and railcars are placed on them.
In addition, the same number of tracks for temporarily storing railcars (siding tracks) are provided at the tail end of the departure tracks.
By moving railcars appropriately between the departure tracks and the siding tracks, the goal is to arrange the railcars on each departure track in the prescribed order.

When performing multiple moves simultaneously, if the routes connecting departure tracks and siding tracks intersect, the railcars block each other's paths. Therefore, the moves performed at the same time must be chosen so that their routes do not intersect.

For Takahashi Railway, arrange all railcars in the prescribed order in as few steps as possible.

### Problem Statement

There are R departure tracks arranged in the freight terminal, and R siding tracks are placed on the side opposite to the exits of the departure tracks.
The departure tracks and the siding tracks are numbered 0,1,\ldots,R-1 from left to right.
Hereafter, for a departure track, the end on the exit side is called the "front", and the opposite end is called the "rear". For a siding track, the end closer to the departure tracks is called the "front", and the opposite end is called the "rear".

Every departure track is connected by rails to every siding track, and railcars can be moved between departure tracks and siding tracks.
Each departure track has a capacity of 15 railcars, and each siding track has a capacity of 20 railcars. Any move that would exceed these capacities is prohibited.

Initially, each departure track contains 10 railcars.
Each railcar is assigned a unique ID from 0,\ldots,10R-1 , and the ID of the railcar placed at the c -th position from the front of departure track r is Y_{r,c} . All siding tracks are empty.
By moving railcars between departure tracks and siding tracks, the goal is to arrange, for each departure track r , the railcars with IDs 10r, 10r+1, \ldots, 10r+9 in this order from the front.

In each turn, you may perform multiple moves simultaneously from the following two types of moves. Each move handles k consecutive railcars ( k \ge 1 ), and their order is preserved.

- (type = 0) Take k consecutive railcars from the rear of departure track i and attach them to the front of siding track j .- (type = 1) Take k consecutive railcars from the front of siding track j and attach them to the rear of departure track i .

To ensure safe train operations, the moves performed in the same turn must be chosen so that their routes do not intersect, regardless of direction. That is, the following two conditions must be satisfied.

- A departure track or siding track must not be used more than once in the same turn.- If a move between departure track i_1 and siding track j_1 , and a move between departure track i_2 and siding track j_2 are performed simultaneously, then if i_1 < i_2 , it must hold that j_1 < j_2 .

You may perform at most 4000 turns of moves.

### Scoring

Let T be the number of turns in the output sequence of moves.

If all departure tracks exactly match the target configuration, the score is 100R + 4000 - T .

Otherwise, the score is the sum of the following points over each railcar placed on the departure tracks in the final state (at most 10R railcars).

- 1 point if the railcar is placed on the correct departure track- An additional 9 points if its position from the front is also correct

If the number of turns exceeds 4000, or if the output violates the non-intersection constraint or the capacity constraint of any track, the submission is judged as WA .

There are 150 test cases, and the score of a submission is the total score for each test case.
If your submission produces an illegal output or exceeds the time limit for some test cases, the submission itself will be judged as WA or TLE , and the score of the submission will be zero.
The highest score obtained during the contest will determine the final ranking, and there will be no system test after the contest.
If more than one participant gets the same score, they will be ranked in the same place regardless of the submission time.

### Input

The input is given from Standard Input in the following format:

```
R
Y_{0,0} \cdots Y_{0,9}
\vdots
Y_{R-1,0} \cdots Y_{R-1,9}
```

- In every test case, R = 10 .- Y_{r,c} is the ID of the railcar placed at the c -th position from the front of departure track r in the initial state ( 0 \leq c < 10 ).- Y_{r,c} contains each of 0,\ldots,10R-1 exactly once.

### Output

Print the sequence of moves to Standard Output in the following format:

```
T
K_0
\mathrm{type} i j k
\vdots
\mathrm{type} i j k
\vdots
K_{T-1}
\mathrm{type} i j k
\vdots
\mathrm{type} i j k
```

Here, T is the number of turns in which moves are performed ( T \leq 4000 ).
After printing T , for each turn t = 0, 1, \cdots, T-1 , print the following in this order.

- First, print the number of moves performed in that turn, K_t , on a single line ( 1 \leq K_t \leq R ).- Then, print each of the moves performed in that turn on the following K_t lines in the format type i j k ( \mathrm{type} \in \{0,1\} , 0 \leq i,j < R , k \geq 1 ). If \mathrm{type} = 0 , take k railcars from the rear of departure track i and attach them to the front of siding track j . If \mathrm{type} = 1 , take k railcars from the front of siding track j and attach them to the rear of departure track i .

Show example

### Input Generation

In every test case, R = 10 .

Generate a uniformly random permutation of the integer sequence 0,1,\ldots,10R-1 , and assign the elements in order to Y_{0,0}, Y_{0,1}, \ldots, Y_{0,9}, Y_{1,0}, \ldots, Y_{R-1,9} .

### Tools (Input generator and visualizer)
- Web version : This is more powerful than the local version providing animations.- Local version : You need a compilation environment of Rust language . Pre-compiled binary for Windows : If you are not familiar with the Rust language environment, please use this instead.

Please be aware that sharing visualization results or discussing solutions/ideas during the contest is prohibited.
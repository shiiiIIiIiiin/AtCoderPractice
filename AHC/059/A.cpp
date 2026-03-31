#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int N;
vector<vector<int>> board; // 盤面のカード番号（-1なら空）
vector<pair<int,int>> cardPos[200]; // cardPos[num] = {(x1,y1), (x2,y2)} ペアの位置
int curX, curY;
vector<int> hand; // 山札（スタック）
string result; // 出力する操作列
double globalAlpha = 2.0; // グローバルなαパラメータ
double globalCenterBonus = 0.5; // 中心ボーナスの係数

// マンハッタン距離
int dist(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// (x1,y1)から(x2,y2)へ移動する操作列を生成して実行
void moveTo(int tx, int ty) {
    while (curX < tx) { result += 'D'; curX++; }
    while (curX > tx) { result += 'U'; curX--; }
    while (curY < ty) { result += 'R'; curY++; }
    while (curY > ty) { result += 'L'; curY--; }
}

// cardPosから指定位置を削除
void removeFromCardPos(int num, int x, int y) {
    auto& pos = cardPos[num];
    pos.erase(remove(pos.begin(), pos.end(), make_pair(x, y)), pos.end());
}

// カードnumのペアの位置を取得（指定位置以外）
pair<int,int> getPairPos(int num, int excludeX, int excludeY) {
    for (auto& p : cardPos[num]) {
        if (p.first != excludeX || p.second != excludeY) return p;
    }
    return {-1, -1};
}

// 現在位置のカードを山札に積む（Z操作）
// 山札の上2枚が同じなら自動的に消える
void pickupToHand() {
    int num = board[curX][curY];
    result += 'Z'; // カードを拾う操作
    removeFromCardPos(num, curX, curY);
    board[curX][curY] = -1;
    
    // 山札の上2枚が同じなら両方消える
    if (!hand.empty() && hand.back() == num) {
        hand.pop_back(); // ペアが揃ったので両方消える
    } else {
        hand.push_back(num); // 揃わなければ積む
    }
}

// 現在位置のカードと山札トップをマッチングして消す（Z操作）
// pickupToHandと同じ処理になる
void matchAndRemove() {
    pickupToHand();
}

// スタックトップのカードを現在位置に置く（X操作）
void placeCard() {
    if (hand.empty()) return;
    if (board[curX][curY] != -1) return; // 空マスでないと置けない
    
    int num = hand.back();
    hand.pop_back();
    board[curX][curY] = num;
    cardPos[num].push_back({curX, curY});
    result += 'X';
}

// (sx, sy) から (ex, ey) への移動で、点(px, py)を経由しても最短距離か判定
// 最短距離 = 逆戻りしない = 単調に進む
bool isOnShortestPath(int sx, int sy, int ex, int ey, int px, int py) {
    // pが(sx,sy)と(ex,ey)を対角とする長方形内にあるか
    int minX = min(sx, ex), maxX = max(sx, ex);
    int minY = min(sy, ey), maxY = max(sy, ey);
    return (px >= minX && px <= maxX && py >= minY && py <= maxY);
}

// (sx,sy) → (px1,py1) → (px2,py2) → (ex,ey) が最短距離か判定
bool isDetourOnShortestPath(int sx, int sy, int ex, int ey, int px1, int py1, int px2, int py2) {
    // 3区間すべてが「逆戻りしない」経路である必要がある
    // = px1が(sx,sy)→(ex,ey)の長方形内
    // = px2が(px1,py1)→(ex,ey)の長方形内
    // = 全体の距離が直接距離と同じ
    
    int directDist = abs(ex - sx) + abs(ey - sy);
    int detourDist = abs(px1 - sx) + abs(py1 - sy) 
                   + abs(px2 - px1) + abs(py2 - py1) 
                   + abs(ex - px2) + abs(ey - py2);
    
    if (detourDist != directDist) return false;
    
    // さらに、各点が正しい順序で並んでいるか確認
    // (sx,sy) → (px1,py1) が逆戻りしない
    if (!isOnShortestPath(sx, sy, ex, ey, px1, py1)) return false;
    // (px1,py1) → (px2,py2) が (px1,py1) → (ex,ey) の逆戻りしない
    if (!isOnShortestPath(px1, py1, ex, ey, px2, py2)) return false;
    
    return true;
}

// (x1,y1)から(x2,y2)へ向かう途中で寄り道できるペアを再帰的に探す
// 再帰的に見つけたペアを入れ子で処理するための構造体
struct DetourInfo {
    int num;
    int x1, y1, x2, y2;
    vector<DetourInfo> inner; // 内側の寄り道（x1,y1→x2,y2の間で処理）
};

DetourInfo findDetourPairsRecursive(int x1, int y1, int x2, int y2, set<int>& used) {
    DetourInfo result = {-1, x1, y1, x2, y2, {}};
    
    int bestNum = -1;
    int bestDist = -1;
    int bx1, by1, bx2, by2;
    
    // 全カードを探索して、最短経路上にあるペアを探す
    for (int num = 0; num < 200; num++) {
        if (used.count(num)) continue;
        if (cardPos[num].size() != 2) continue;
        
        auto& positions = cardPos[num];
        int px1 = positions[0].first, py1 = positions[0].second;
        int px2 = positions[1].first, py2 = positions[1].second;
        
        // パターン1: (x1,y1) → (px1,py1) → (px2,py2) → (x2,y2)
        if (isDetourOnShortestPath(x1, y1, x2, y2, px1, py1, px2, py2)) {
            int pairDist = abs(px2 - px1) + abs(py2 - py1);
            if (pairDist > bestDist) {
                bestDist = pairDist;
                bestNum = num;
                bx1 = px1; by1 = py1; bx2 = px2; by2 = py2;
            }
        }
        // パターン2: (x1,y1) → (px2,py2) → (px1,py1) → (x2,y2)
        else if (isDetourOnShortestPath(x1, y1, x2, y2, px2, py2, px1, py1)) {
            int pairDist = abs(px2 - px1) + abs(py2 - py1);
            if (pairDist > bestDist) {
                bestDist = pairDist;
                bestNum = num;
                bx1 = px2; by1 = py2; bx2 = px1; by2 = py1;
            }
        }
    }
    
    if (bestNum == -1) {
        return result; // 寄り道なし
    }
    
    used.insert(bestNum);
    result.num = bestNum;
    result.x1 = bx1; result.y1 = by1;
    result.x2 = bx2; result.y2 = by2;
    
    // 再帰: n2のペア(bx1,by1)→(bx2,by2)の間でさらに寄り道を探す
    DetourInfo inner = findDetourPairsRecursive(bx1, by1, bx2, by2, used);
    if (inner.num != -1) {
        result.inner.push_back(inner);
    }
    
    return result;
}

// DetourInfoを再帰的に処理（入れ子構造を正しく処理）
void processDetour(const DetourInfo& detour) {
    if (detour.num == -1) return;
    
    // カードがまだあるか確認
    if (board[detour.x1][detour.y1] != detour.num) return;
    if (board[detour.x2][detour.y2] != detour.num) return;
    
    // 1. 拾う位置へ移動して拾う
    moveTo(detour.x1, detour.y1);
    pickupToHand();
    
    // 2. 内側の寄り道を処理（拾う→消すの間で）
    for (const auto& inner : detour.inner) {
        processDetour(inner);
    }
    
    // 3. 消す位置へ移動して消す
    moveTo(detour.x2, detour.y2);
    matchAndRemove();
}

// ペアを処理する（現在位置のカードを拾って、ペアの位置でZする）
void processSinglePair(int num, int pairX, int pairY) {
    pickupToHand();
    moveTo(pairX, pairY);
    matchAndRemove();
}

// ペアを処理する（寄り道リストも含めて）
void processPairWithDetours() {
    if (board[curX][curY] == -1) return;
    
    int startNum = board[curX][curY];
    auto pairPos = getPairPos(startNum, curX, curY);
    if (pairPos.first == -1) return;
    
    int sx = curX, sy = curY;
    int px = pairPos.first, py = pairPos.second;
    
    // 寄り道情報を再帰的に取得（startNumは除外して探索）
    set<int> used;
    used.insert(startNum);
    DetourInfo detour = findDetourPairsRecursive(sx, sy, px, py, used);
    
    // まず現在位置のカードを拾う
    pickupToHand();
    
    // 寄り道を入れ子で処理（n2拾う → n3処理 → n2消す の順）
    if (detour.num != -1) {
        // detourはstartNumの拾う→消すの間で処理するべき寄り道
        processDetour(detour);
    }
    
    // 最終目的地（startNumのペア）へ移動してマッチング
    moveTo(px, py);
    matchAndRemove();
}

// 移動中にカードを拾って空マスに置くことでペア間距離を縮小する
// 戻り値: {拾うカード位置, 置く空マス位置, カード番号, 縮小距離}
struct RelocateInfo {
    int pickX, pickY;   // カードを拾う位置
    int placeX, placeY; // カードを置く位置
    int cardNum;        // カード番号
    int distReduction;  // 距離の縮小量
};

// (sx,sy)から(ex,ey)への最短経路上で、カードを拾って空マスに置く最良の操作を探す
// targetNumは処理対象外（今向かっているペア）
RelocateInfo findBestRelocate(int sx, int sy, int ex, int ey, int targetNum) {
    RelocateInfo best = {-1, -1, -1, -1, -1, 0};
    
    // 盤面の中心
    int centerX = N / 2;
    int centerY = N / 2;
    
    // 最短経路上の全マスを列挙
    int minX = min(sx, ex), maxX = max(sx, ex);
    int minY = min(sy, ey), maxY = max(sy, ey);
    
    // 最短経路上のカードと空マスを探す
    for (int num = 0; num < 200; num++) {
        if (num == targetNum) continue;
        if (cardPos[num].size() != 2) continue;
        
        auto& positions = cardPos[num];
        
        // 各カード位置について
        for (int i = 0; i < 2; i++) {
            int cardX = positions[i].first;
            int cardY = positions[i].second;
            int pairX = positions[1-i].first;
            int pairY = positions[1-i].second;
            
            // カードが最短経路上にあるか
            if (cardX < minX || cardX > maxX || cardY < minY || cardY > maxY) continue;
            
            int currentPairDist = dist(cardX, cardY, pairX, pairY);
            
            // このカードに対して、最良の空マスを見つける
            // スコア = ペア間距離の縮小 + 中心への近さのボーナス
            int bestEmptyX = -1, bestEmptyY = -1;
            double bestScore = 0;
            
            // 最短経路上の空マスを探す
            for (int emptyX = minX; emptyX <= maxX; emptyX++) {
                for (int emptyY = minY; emptyY <= maxY; emptyY++) {
                    if (board[emptyX][emptyY] != -1) continue; // 空マスでない
                    if (emptyX == cardX && emptyY == cardY) continue; // 同じ位置
                    
                    // カードを拾う→空マスに置く が最短経路上で可能か
                    int detourDist = dist(sx, sy, cardX, cardY) 
                                   + dist(cardX, cardY, emptyX, emptyY)
                                   + dist(emptyX, emptyY, ex, ey);
                    int directDist = dist(sx, sy, ex, ey);
                    
                    if (detourDist != directDist) continue; // 最短経路でない
                    
                    // 新しいペア間距離
                    int newPairDist = dist(emptyX, emptyY, pairX, pairY);
                    int reduction = currentPairDist - newPairDist;
                    
                    if (reduction <= 0) continue; // 縮小しないならスキップ
                    
                    // 中心への近さ（現在位置との差）
                    int currentCenterDist = dist(cardX, cardY, centerX, centerY);
                    int newCenterDist = dist(emptyX, emptyY, centerX, centerY);
                    int centerBonus = currentCenterDist - newCenterDist; // 中心に近づくほど+
                    
                    // スコア = 距離縮小 + 中心ボーナス * globalCenterBonus
                    double score = reduction + centerBonus * globalCenterBonus;
                    
                    if (score > bestScore) {
                        bestScore = score;
                        bestEmptyX = emptyX;
                        bestEmptyY = emptyY;
                    }
                }
            }
            
            // このカードで改善できる場合
            if (bestEmptyX != -1) {
                int newPairDist = dist(bestEmptyX, bestEmptyY, pairX, pairY);
                int reduction = currentPairDist - newPairDist;
                
                // 中心ボーナスも含めた総合スコアで比較
                int currentCenterDist = dist(cardX, cardY, centerX, centerY);
                int newCenterDist = dist(bestEmptyX, bestEmptyY, centerX, centerY);
                int centerBonus = currentCenterDist - newCenterDist;
                double totalScore = reduction + centerBonus * globalCenterBonus;
                
                if (totalScore > best.distReduction) {
                    best = {cardX, cardY, bestEmptyX, bestEmptyY, num, (int)totalScore};
                }
            }
        }
    }
    
    return best;
}

// バランス型：ペア間距離と移動距離のバランスでカードを選ぶ
// スコア = ペア間距離 - 移動距離 * α

pair<int,int> findBestBalancedCard() {
    int bestScore = INT_MIN;
    pair<int,int> best = {-1, -1};

    for (int num = 0; num < 200; num++) {
        if (cardPos[num].size() != 2) continue;

        auto& positions = cardPos[num];
        int x1 = positions[0].first, y1 = positions[0].second;
        int x2 = positions[1].first, y2 = positions[1].second;

        int pairDist = abs(x2 - x1) + abs(y2 - y1);
        int d1 = dist(curX, curY, x1, y1);
        int d2 = dist(curX, curY, x2, y2);
        int minDist = min(d1, d2);

        int score = pairDist - minDist * globalAlpha;

        if (score > bestScore) {
            bestScore = score;
            if (d1 <= d2) {
                best = {x1, y1};
            } else {
                best = {x2, y2};
            }
        }
    }
    return best;
}

// 盤面にカードが残っているか
bool hasCards() {
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            if (board[x][y] != -1) return true;
        }
    }
    return false;
}

// 移動回数をカウント（U/D/L/Rのみ、Zは含まない）
int countMoves(const string& s) {
    int cnt = 0;
    for (char c : s) {
        if (c == 'U' || c == 'D' || c == 'L' || c == 'R') cnt++;
    }
    return cnt;
}

vector<int> processOrder; // 処理したカード番号の順序を記録

// 1回のシミュレーションを実行して結果を返す
// useRelocate: trueならX操作による再配置を使う
// recordOrder: trueなら処理順序を記録
string runSimulation(vector<vector<int>> initBoard, vector<pair<int,int>> initCardPos[200],
                     bool useRelocate = false, bool recordOrder = false) {
    // 状態をリセット
    board = initBoard;
    for (int i = 0; i < 200; i++) {
        cardPos[i] = initCardPos[i];
    }
    curX = 0; curY = 0;
    hand.clear();
    result.clear();
    if (recordOrder) processOrder.clear();

    while (hasCards()) {
        if (board[curX][curY] != -1) {
            if (recordOrder) processOrder.push_back(board[curX][curY]);
            processPairWithDetours();
        } else {
            auto [nx, ny] = findBestBalancedCard();
            if (nx == -1) break;

            int targetNum = board[nx][ny];
            if (recordOrder) processOrder.push_back(targetNum);

            // X操作による再配置（オプション）
            if (useRelocate) {
                while (true) {
                    RelocateInfo reloc = findBestRelocate(curX, curY, nx, ny, targetNum);
                    if (reloc.distReduction <= 0) break;

                    moveTo(reloc.pickX, reloc.pickY);
                    pickupToHand();
                    moveTo(reloc.placeX, reloc.placeY);
                    placeCard();
                }
            }

            // n1へ向かう途中でも寄り道できるカードを処理
            set<int> used;
            used.insert(targetNum);
            DetourInfo detour = findDetourPairsRecursive(curX, curY, nx, ny, used);

            // 寄り道を入れ子で処理しながらn1へ向かう
            if (detour.num != -1) {
                processDetour(detour);
            }

            // n1の位置へ移動
            moveTo(nx, ny);
        }
    }

    return result;
}

// 指定した順序でカードを処理するシミュレーション
string runSimulationWithOrder(vector<vector<int>> initBoard, vector<pair<int,int>> initCardPos[200],
                              const vector<int>& order) {
    // 状態をリセット
    board = initBoard;
    for (int i = 0; i < 200; i++) {
        cardPos[i] = initCardPos[i];
    }
    curX = 0; curY = 0;
    hand.clear();
    result.clear();

    set<int> orderSet(order.begin(), order.end());

    for (int num : order) {
        if (cardPos[num].size() != 2) continue; // 既に処理済み

        // numの位置を取得（近い方を選ぶ）
        auto& positions = cardPos[num];
        int x1 = positions[0].first, y1 = positions[0].second;
        int x2 = positions[1].first, y2 = positions[1].second;
        int d1 = dist(curX, curY, x1, y1);
        int d2 = dist(curX, curY, x2, y2);

        int nx = (d1 <= d2) ? x1 : x2;
        int ny = (d1 <= d2) ? y1 : y2;

        // 目的地へ向かう途中で寄り道（orderSetに含まれないカードのみ）
        set<int> used = orderSet;
        DetourInfo detour = findDetourPairsRecursive(curX, curY, nx, ny, used);
        if (detour.num != -1) {
            processDetour(detour);
        }

        // 目的地へ移動してペアを処理
        moveTo(nx, ny);
        if (board[curX][curY] != -1) {
            int startNum = board[curX][curY];
            auto pairPos = getPairPos(startNum, curX, curY);
            if (pairPos.first != -1) {
                int px = pairPos.first, py = pairPos.second;
                set<int> used2 = orderSet;
                DetourInfo detour2 = findDetourPairsRecursive(curX, curY, px, py, used2);

                pickupToHand();
                if (detour2.num != -1) {
                    processDetour(detour2);
                }
                moveTo(px, py);
                matchAndRemove();
            }
        }
    }

    // 残ったカードを貪欲に処理
    while (hasCards()) {
        if (board[curX][curY] != -1) {
            processPairWithDetours();
        } else {
            auto [nx, ny] = findBestBalancedCard();
            if (nx == -1) break;

            set<int> used;
            int targetNum = board[nx][ny];
            used.insert(targetNum);
            DetourInfo detour = findDetourPairsRecursive(curX, curY, nx, ny, used);

            if (detour.num != -1) {
                processDetour(detour);
            }
            moveTo(nx, ny);
        }
    }

    return result;
}

int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    
    cin >> N;
    board.resize(N, vector<int>(N));
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
            cardPos[board[i][j]].push_back({i, j});
        }
    }
    
    // 初期状態を保存
    vector<vector<int>> initBoard = board;
    vector<pair<int,int>> initCardPos[200];
    for (int i = 0; i < 200; i++) {
        initCardPos[i] = cardPos[i];
    }
    
    // パラメータ探索
    string bestResult;
    double bestAlpha = 2.5;
    int bestMoves = INT_MAX;
    bool bestUseRelocate = false;

    // 時間計測
    auto startTime = chrono::high_resolution_clock::now();
    const double TIME_LIMIT = 1.9;

    vector<int> bestOrder;

    // Phase 1: X操作なしでαを探索（高速・安定）+ 処理順序を記録
    globalCenterBonus = 0.0;
    for (int a = 200; a <= 300; a += 5) {  // さらに範囲を縮小
        globalAlpha = a / 100.0;
        string res = runSimulation(initBoard, initCardPos, false, true);
        int moves = countMoves(res);

        if (moves < bestMoves) {
            bestMoves = moves;
            bestResult = res;
            bestAlpha = globalAlpha;
            bestUseRelocate = false;
            bestOrder = processOrder;
        }
    }

    int greedyBest = bestMoves;
    cerr << "Greedy best: alpha=" << bestAlpha << ", moves=" << bestMoves << endl;

    // Phase 2: X操作ありで試す（最良のαの周辺で）- 軽量化
    for (int a = (int)(bestAlpha * 100) - 30; a <= (int)(bestAlpha * 100) + 30; a += 10) {
        if (a < 100 || a > 400) continue;
        globalAlpha = a / 100.0;
        for (int cb = 0; cb <= 10; cb += 5) {
            globalCenterBonus = cb / 10.0;
            string res = runSimulation(initBoard, initCardPos, true, true);
            int moves = countMoves(res);

            if (moves < bestMoves) {
                bestMoves = moves;
                bestResult = res;
                bestAlpha = globalAlpha;
                bestUseRelocate = true;
                bestOrder = processOrder;
            }
        }
    }

    int relocateBest = bestMoves;
    cerr << "After relocate: moves=" << bestMoves << endl;

    // Phase 3: 2-opt改善（処理順序の部分反転）- 時間制限付き
    globalAlpha = bestAlpha;
    vector<int> currentOrder = bestOrder;
    int currentScore = bestMoves;

    for (int i = 0; i < (int)currentOrder.size() - 1; i += 2) {  // 2つ飛ばし
        auto now = chrono::high_resolution_clock::now();
        double elapsed = chrono::duration<double>(now - startTime).count();
        if (elapsed > TIME_LIMIT * 0.7) break;

        for (int j = i + 2; j < min((int)currentOrder.size(), i + 6); j++) {
            vector<int> newOrder = currentOrder;
            reverse(newOrder.begin() + i + 1, newOrder.begin() + j + 1);

            string res = runSimulationWithOrder(initBoard, initCardPos, newOrder);
            int moves = countMoves(res);

            if (moves < currentScore) {
                currentScore = moves;
                currentOrder = newOrder;

                if (moves < bestMoves) {
                    bestMoves = moves;
                    bestResult = res;
                    bestOrder = newOrder;
                    cerr << "2-opt improved: " << moves << endl;
                }
            }
        }
    }

    // Phase 4は削除（時間節約）

    // デバッグ出力（標準エラー）
    cerr << "Final: moves=" << bestMoves << " (greedy=" << greedyBest
         << ", relocate=" << relocateBest << ")" << endl;
    
    // 最良の結果を出力
    for (char c : bestResult) {
        cout << c << '\n';
    }
    
    return 0;
}
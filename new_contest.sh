#!/bin/bash
# Usage: new_contest 401
#        new_contest ABC401

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
TEMPLATE="$SCRIPT_DIR/sample.cpp"

# "ABC" プレフィックスを除去して番号だけ取り出す
INPUT="$1"
NUM="${INPUT#ABC}"
NUM="${NUM#abc}"

if [ -z "$NUM" ]; then
    echo "Usage: new_contest <number> (e.g. 401 or ABC401)"
    exit 1
fi

TARGET="$SCRIPT_DIR/ABC/$NUM"

if [ -d "$TARGET" ]; then
    echo "Already exists: $TARGET"
    exit 1
fi

OJ="/c/Users/kimura/AppData/Local/Programs/Python/Python312/Scripts/oj"
NUM_LOWER="${NUM,,}"

mkdir -p "$TARGET"

for PROB in A B C D E F G; do
    cp "$TEMPLATE" "$TARGET/$PROB.cpp"
    PROB_LOWER="${PROB,,}"
    echo "[$PROB] Downloading samples..."
    (cd "$TARGET" && "$OJ" d "https://atcoder.jp/contests/abc${NUM_LOWER}/tasks/abc${NUM_LOWER}_${PROB_LOWER}" --directory "test/${PROB_LOWER}" 2>&1 | grep -E "SUCCESS|ERROR|WARNING.*not found")
done

git -C "$SCRIPT_DIR" add "ABC/$NUM/"

echo ""
echo "Done: ABC/$NUM/  (A.cpp ~ G.cpp + samples)"

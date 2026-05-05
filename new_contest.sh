#!/bin/bash
# Usage: new_contest ABC401
#        new_contest ARC190
#        new_contest AGC070
#        new_contest AWC13      # AWCは4桁ゼロ埋め (awc0013)
#        new_contest 401        # 数字のみはABC扱い
#        new_contest EDPC       # 問題集（テンプレートのみ作成）
#        new_contest FPS
#        new_contest TESSOKU
#        new_contest TYPICAL90

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
TEMPLATE="$SCRIPT_DIR/sample.cpp"

# 問題番号 → ラベル (1=a, 26=z, 27=aa, ...)
nth_label() {
    local n=$1 result="" letters="abcdefghijklmnopqrstuvwxyz"
    while [ $n -gt 0 ]; do
        n=$((n - 1))
        result="${letters:$((n % 26)):1}${result}"
        n=$((n / 26))
    done
    echo "$result"
}

INPUT="${1^^}"  # 大文字に統一

# 問題集の処理（数字なし・テンプレートのみ作成）
declare -A PS_COUNT
PS_COUNT["EDPC"]=26
PS_COUNT["FPS"]=24
PS_COUNT["TESSOKU"]=174
PS_COUNT["TYPICAL90"]=90

if [ -n "${PS_COUNT[$INPUT]+x}" ]; then
    TARGET="$SCRIPT_DIR/$INPUT"
    COUNT="${PS_COUNT[$INPUT]}"

    if [ -d "$TARGET" ]; then
        echo "Already exists: $TARGET"
        exit 1
    fi

    mkdir -p "$TARGET"
    for i in $(seq 1 $COUNT); do
        LABEL=$(nth_label $i)
        cp "$TEMPLATE" "$TARGET/${LABEL^^}.cpp"
    done

    git -C "$SCRIPT_DIR" add "$INPUT/"
    echo "Done: $INPUT/  ($COUNT problems, テンプレートのみ)"
    echo "テストケースは: dl $INPUT <番号>"
    exit 0
fi

# プレフィックスと番号を分離
if [[ "$INPUT" =~ ^([A-Z]+)([0-9]+)$ ]]; then
    PREFIX="${BASH_REMATCH[1]}"
    NUM="${BASH_REMATCH[2]}"
elif [[ "$INPUT" =~ ^([0-9]+)$ ]]; then
    PREFIX="ABC"
    NUM="${BASH_REMATCH[1]}"
else
    echo "Usage: new_contest <contest> (e.g. ABC401, ARC190, AGC070)"
    exit 1
fi

# 問題リスト
case "$PREFIX" in
    ABC) PROBS="A B C D E F G" ;;
    AWC) PROBS="A B C D E" ;;
    *)   PROBS="A B C D E F" ;;
esac

PREFIX_LOWER="${PREFIX,,}"
# AWCはURL上で4桁ゼロ埋め (awc0013)、それ以外はそのまま
if [ "$PREFIX" = "AWC" ]; then
    NUM_LOWER="$(printf '%04d' "$((10#$NUM))")"
else
    NUM_LOWER="${NUM,,}"
fi
TARGET="$SCRIPT_DIR/${PREFIX}/${NUM}"

if [ -d "$TARGET" ]; then
    echo "Already exists: $TARGET"
    exit 1
fi

OJ="/c/Users/kimura/AppData/Local/Programs/Python/Python312/Scripts/oj"

mkdir -p "$TARGET"

for PROB in $PROBS; do
    cp "$TEMPLATE" "$TARGET/$PROB.cpp"
    PROB_LOWER="${PROB,,}"
    echo "[$PROB] Downloading samples..."
    (cd "$TARGET" && "$OJ" d "https://atcoder.jp/contests/${PREFIX_LOWER}${NUM_LOWER}/tasks/${PREFIX_LOWER}${NUM_LOWER}_${PROB_LOWER}" --directory "test/${PROB_LOWER}" 2>&1 | grep -E "SUCCESS|ERROR|WARNING.*not found")
done

git -C "$SCRIPT_DIR" add "${PREFIX}/${NUM}/"

echo ""
echo "Done: ${PREFIX}/${NUM}/  ($(echo $PROBS | tr ' ' ',').cpp + samples)"

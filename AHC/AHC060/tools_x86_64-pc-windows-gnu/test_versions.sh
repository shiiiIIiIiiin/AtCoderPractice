#!/bin/bash

# Compile all versions
echo "Compiling versions..."
g++ -O3 -o main.exe main.cpp
g++ -O3 -o v1.exe v1_threshold3_change30.cpp
g++ -O3 -o v2.exe v2_threshold3_change60.cpp
g++ -O3 -o v3.exe v3_threshold5_change30.cpp
g++ -O3 -o v4.exe v4_threshold5_change60.cpp

echo "Testing on multiple seeds..."
echo ""
echo "Seed | Main(4,45) | V1(3,30) | V2(3,60) | V3(5,30) | V4(5,60)"
echo "-----+-----------+----------+----------+----------+----------"

for seed in 0000 0001 0002 0003 0004 0005 0006 0007 0008 0009; do
    printf "%s |" "$seed"
    
    for exe in main.exe v1.exe v2.exe v3.exe v4.exe; do
        ./$exe < in/$seed.txt > out.txt 2>/dev/null
        score=$(./vis.exe in/$seed.txt out.txt 2>&1 | grep "Score = " | grep -oE "[0-9]+")
        printf " %9s |" "$score"
    done
    printf "\n"
done

echo ""
echo "Computing averages..."
totals=(0 0 0 0 0)
count=0

for seed in 0000 0001 0002 0003 0004 0005 0006 0007 0008 0009; do
    for i in {0..4}; do
        case $i in
            0) exe="main.exe" ;;
            1) exe="v1.exe" ;;
            2) exe="v2.exe" ;;
            3) exe="v3.exe" ;;
            4) exe="v4.exe" ;;
        esac
        ./${exe} < in/${seed}.txt > out.txt 2>/dev/null
        score=$(./vis.exe in/${seed}.txt out.txt 2>&1 | grep "Score = " | grep -oE "[0-9]+")
        totals[$i]=$((${totals[$i]} + score))
    done
    count=$((count + 1))
done

echo ""
echo "Averages (over $count seeds):"
echo "Main(4,45): $((${totals[0]} / count))"
echo "V1(3,30):   $((${totals[1]} / count))"
echo "V2(3,60):   $((${totals[2]} / count))"
echo "V3(5,30):   $((${totals[3]} / count))"
echo "V4(5,60):   $((${totals[4]} / count))"

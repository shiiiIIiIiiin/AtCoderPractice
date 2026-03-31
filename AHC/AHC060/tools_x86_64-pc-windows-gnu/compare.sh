#!/bin/bash

WORKDIR="$(cd "$(dirname "$0")" && pwd)"
cd "$WORKDIR"

echo "Compiling versions..."
g++ -O2 -std=c++17 main.cpp -o main_linear
g++ -O2 -std=c++17 main_exp_cooling.cpp -o main_exp

if [ ! -f main_linear ] || [ ! -f main_exp ]; then
    echo "Compilation failed!"
    exit 1
fi

echo "Testing both versions on first 3 seeds (faster test)..."
echo ""

total_linear=0
total_exp=0
count=0

for i in 0 1 2; do
    seed=$(printf "%04d" $i)
    input_file="in/${seed}.txt"
    
    if [ ! -f "$input_file" ]; then
        echo "Warning: $input_file not found"
        continue
    fi
    
    # Run linear version and count output lines (score = number of deliveries)
    echo "Running Seed $seed..."
    output_linear=$(timeout 5 ./main_linear < "$input_file" 2>/dev/null | wc -l)
    
    # Run exponential version
    output_exp=$(timeout 5 ./main_exp < "$input_file" 2>/dev/null | wc -l)
    
    echo "  Linear=$output_linear, Exponential=$output_exp"
    
    total_linear=$((total_linear + output_linear))
    total_exp=$((total_exp + output_exp))
    count=$((count + 1))
done

echo ""
echo "=== Summary (3 seeds) ==="
if [ $count -gt 0 ]; then
    avg_linear=$((total_linear / count))
    avg_exp=$((total_exp / count))
    echo "Linear (main.cpp):         Total=$total_linear, Average=$avg_linear"
    echo "Exponential (exp_cooling): Total=$total_exp, Average=$avg_exp"
    echo ""
    
    if [ $avg_exp -gt $avg_linear ]; then
        diff=$((avg_exp - avg_linear))
        echo "✓ Exponential is better by ~$diff points per seed"
    elif [ $avg_exp -lt $avg_linear ]; then
        diff=$((avg_linear - avg_exp))
        echo "✗ Linear is better by ~$diff points per seed"
    else
        echo "= Same performance"
    fi
fi

echo ""
echo "Cleanup..."
rm -f main_linear main_exp

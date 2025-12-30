#!/bin/bash

echo "=== COMP1001 MMM Benchmark ==="

gcc-15 mmm.c -O3 -fopenmp -o mmm || exit 1

THREADS=$1

for N in 64 128 256 512 1024 2048
do
    echo "Running N=$N Threads=$THREADS"
    ./mmm $N $THREADS
    echo "-----------------------------"
done

echo "=== Done ==="

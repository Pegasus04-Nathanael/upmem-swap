#!/bin/bash

echo "=== UPMEM FULL BENCHMARK SUITE ==="
echo ""

# Create directories
mkdir -p build plots scripts

# Compile DPU program
echo "[1/4] Compiling DPU program with tasklets..."
/opt/upmem-sdk-2025.1.0/bin/dpu-clang \
    -I/opt/upmem-sdk-2025.1.0/include \
    -I/opt/upmem-sdk-2025.1.0/include/dpu \
    -O2 -D__DPU__ \
    -o build/dpu_tasklets \
    src/dpu/swap_tasklets.c
echo "✓ DPU compiled"
echo ""

# Compile host benchmark
echo "[2/4] Compiling host benchmark..."
gcc -I/opt/upmem-sdk-2025.1.0/include \
    -I/opt/upmem-sdk-2025.1.0/include/dpu \
    -o build/benchmark_complete \
    src/host/benchmark_complete.c \
    -L/opt/upmem-sdk-2025.1.0/lib -ldpu -lm \
    -Wl,-rpath,/opt/upmem-sdk-2025.1.0/lib
echo "✓ Host benchmark compiled"
echo ""

# Run benchmark
echo "[3/4] Running comprehensive benchmark..."
echo "This will take approximately 30-60 minutes..."
./build/benchmark_complete
echo ""

# Generate plots
echo "[4/4] Generating visualizations..."
python3 scripts/visualize_results.py
echo ""

echo "=== BENCHMARK COMPLETE ==="
echo "Results: benchmark_results.csv"
echo "Plots: plots/*.png"

#!/usr/bin/env bash
set -euo pipefail

# Simple benchmark runner for build/host
# Usage: ./scripts/run_benchmark.sh [iterations]

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
HOST_BIN="$ROOT_DIR/build/host"
SDK_LIB_DIR="/opt/upmem-sdk-2025.1.0/lib"
ITER=${1:-10}

if [ ! -x "$HOST_BIN" ]; then
  echo "Error: host binary not found or not executable: $HOST_BIN"
  exit 2
fi

echo "Running benchmark: $ITER iterations"
vals=()
for i in $(seq 1 $ITER); do
  echo -n "Run $i: "
  out=$(LD_LIBRARY_PATH="$SDK_LIB_DIR" "$HOST_BIN" 2>&1 || true)
  # extract ns value from either DPU or simulated output
  ns=$(printf "%s" "$out" | sed -n 's/.*round-trip transfer: .* in \([0-9]*\) ns.*/\1/p' | tail -n1)
  if [ -z "$ns" ]; then
    echo "no measurement (output below)"
    printf "%s\n" "$out" | sed -n '1,200p'
    continue
  fi
  echo "$ns ns"
  vals+=("$ns")
done

if [ ${#vals[@]} -eq 0 ]; then
  echo "No measurements collected"
  exit 3
fi

printf "%s\n" "${vals[@]}" | awk '
BEGIN{min=1e18;max=0;sum=0;sum2=0;count=0}
{v=$1; if(v<min)min=v; if(v>max)max=v; sum+=v; sum2+=v*v; count++}
END{mean=sum/count; sd=sqrt((sum2/count)-(mean*mean)); printf("count=%d\nmin=%f ns\nmax=%f ns\nmean=%f ns\nsd=%f ns\n",count,min,max,mean,sd)}'

exit 0

#!/bin/bash

# chmod +x test/benchmark.sh
# ./test/benchmark.sh bench.txt

cd "$(dirname "$0")/.." # go to ../test
out_path="$1"

source=0
thread_numbers=(2 4 8 12 16 32)
v_numbers=(5000 10000 20000)
densities=(0.1 0.5 0.9)

for v_number in ${v_numbers[@]}; do  
  for density in ${densities[@]}; do
    echo -e "($v_number, $density)" >> $out_path

    input_path="data/graph-$v_number-$density.bin"
    serial_script="./build/bin/dijkstra -i $input_path -s $source"
    
    serial_ms=$($serial_script)
    echo -e "T(1) = $serial_ms" >> $out_path
      
    for threads in ${thread_numbers[@]}; do
        sleep 1
        parallel_script="$serial_script -p -t $threads"
        parallel_ms=$($parallel_script)
        echo -e "T($threads) = $parallel_ms" >> $out_path
    done
  done
done

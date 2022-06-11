#!/bin/bash

cd "$(dirname "$0")/.."
tmp_path=$(readlink -f test/tmp)
mkdir -p "$tmp_path"

serial_path="$tmp_path/serial.csv"
parallel_path="$tmp_path/parallel.csv"

source=0
threads_number=4
v_numbers=(5000 10000 20000)
densities=(0.1 0.5 0.9)

for v_number in ${v_numbers[@]}; do  
  for density in ${densities[@]}; do
    echo -n "G($v_number, $density): "

    input_path="data/graph-$v_number-$density.bin"
    base_script="./build/bin/dijkstra -i $input_path -s $source"

    serial_time=$(eval "$base_script -r $serial_path") # serial
    parallel_time=$(eval "$base_script -p -t $threads_number -r $parallel_path") # parallel

    if cmp -s "$serial_path" "$parallel_path"; then
      cmp_result="PASSED"
    else
      cmp_result="FAILED"
    fi 

    echo "$cmp_result"
  done
done

# clean
rm "$serial_path"
rm "$parallel_path"
rmdir "$tmp_path" 

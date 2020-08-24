#!/bin/bash
for i in "$@"
do
    echo Testing on $i Threads
    for j in 100 500 1000 2000
    do
    echo Input N = $j
    x="./mat_mul_multi $i < ./Testcase/data_$j.txt > ./Output/data_$j-multi-$i.txt"
    ./perform.sh 5 "$x"
    done
done
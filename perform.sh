#!/bin/bash
calc(){ awk "BEGIN { print "$*" }"; }
times=$1
SCRIPT="$(echo $2)"
cnt=0
sum=0
towrite=""
while [ $cnt -lt $times ]
do
    start=$(date +%s.%3N)
    eval ${SCRIPT}
    cnt=$((cnt + 1 ))
    end=$(date +%s.%6N)
    t=$(echo "$end - $start" | bc)
    echo "Round $cnt  --- Times : $t second."
    sum=$(echo "$t + $sum" | bc)
    sleep .1
    towrite=$towrite$t,
done
avg=$(calc $sum/$times)
towrite=$towrite$avg
echo average : $avg
SCRIPT="echo $towrite >> data.csv"
eval ${SCRIPT}
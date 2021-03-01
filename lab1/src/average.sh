#!/bin/bash

cnt=0
sum=0

for num in $(cat $1) #$1 - stdin
do
	sum=$(($sum + $num))
	cnt=$(( $cnt + 1 ))
done

average=$(($sum/$cnt))
echo "Average is $average" 

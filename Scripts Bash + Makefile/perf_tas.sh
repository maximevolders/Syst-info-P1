#!/bin/bash

echo "thread,time" > mesures_tas.csv
echo "thread,time" > mesures_tatas.csv
for j in {1..8};
do
    for i in {1..5};
    do
		make -s
        echo -n "$j," >> mesures_tas.csv
		echo -n "$j," >> mesures_tatas.csv
        /usr/bin/time -ao mesures_tas.csv -f "%e" ./test_and_set $j 2> /dev/null
        /usr/bin/time -ao mesures_tatas.csv -f "%e" ./test_and_test_and_set $j 2> /dev/null
		make -s clean
    done
done

#python3 graph_tas.py 2> /dev/null
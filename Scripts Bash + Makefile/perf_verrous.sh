#!/bin/bash
# tas = test_and_set
# tatas = test_and_test_and_set
# btatas = backoff_test_and_test_and_set

echo "thread,time" > mesures_tas.csv
echo "thread,time" > mesures_tatas.csv
echo "thread,time" > mesures_btatas.csv
for j in {1..8}; # Nombre de threads = #coeurs*2
do
    for i in {1..5}; # 5 essais par nombre de threads
    do
		make -s
        echo -n "$j," >> mesures_tas.csv
		echo -n "$j," >> mesures_tatas.csv
		echo -n "$j," >> mesures_btatas.csv
        /usr/bin/time -ao mesures_tas.csv -f "%e" ./test_and_set $j 2> /dev/null
        /usr/bin/time -ao mesures_tatas.csv -f "%e" ./test_verrous $j 2> /dev/null
		/usr/bin/time -ao mesures_btatas.csv -f "%e" ./backoff_test_and_test_and_set $j 2> /dev/null
		make -s clean
    done
done

python3 graph_verrous.py 2> /dev/null
#!/bin/bash

echo "thread,time" > mesures1.csv
echo "thread,time" > mesures2.csv
echo "thread,time" > mesures3.csv
for j in {1..8};
do
    for i in {1..5};
    do
		make -s
        echo -n "$j," >> mesures1.csv
		echo -n "$j," >> mesures2.csv
		echo -n "$j," >> mesures3.csv
        /usr/bin/time -ao mesures1.csv -f "%e" ./philo $j 2> /dev/null
		/usr/bin/time -ao mesures2.csv -f "%e" ./prod_cons $j $j 2> /dev/null
		/usr/bin/time -ao mesures3.csv -f "%e" ./lect_ecrv $j $j 2> /dev/null
		make -s clean
    done
done

#python3 graph.py 2> /dev/null
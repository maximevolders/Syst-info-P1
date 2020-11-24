#!/bin/bash

echo "thread,time" > mesures1posix.csv
echo "thread,time" > mesures2posix.csv
echo "thread,time" > mesures3posix.csv

echo "thread,time" > mesures1AttAct.csv
echo "thread,time" > mesures2AttAct.csv
echo "thread,time" > mesures3AttAct.csv
for j in {1..8};
do
    for i in {1..5};
    do
		make -s
        echo -n "$j," >> mesures1posix.csv
		echo -n "$j," >> mesures2posix.csv
		echo -n "$j," >> mesures3posix.csv
		
		echo -n "$j," >> mesures1AttAct.csv
		echo -n "$j," >> mesures2AttAct.csv
		echo -n "$j," >> mesures3AttAct.csv
		
        /usr/bin/time -ao mesures1posix.csv -f "%e" ./philo_posix $j 2> /dev/null
		/usr/bin/time -ao mesures2posix.csv -f "%e" ./prod_cons_posix $j 2> /dev/null
		/usr/bin/time -ao mesures3posix.csv -f "%e" ./lect_ecrv_posix $j 2> /dev/null
		
        /usr/bin/time -ao mesures1AttAct.csv -f "%e" ./philo_att_act $j 2> /dev/null
		/usr/bin/time -ao mesures2AttAct.csv -f "%e" ./prod_cons_att_act $j 2> /dev/null
		/usr/bin/time -ao mesures3AttAct.csv -f "%e" ./lect_ecrv_att_act $j 2> /dev/null
		
		make -s clean
    done
done

python3 graph.py 2> /dev/null

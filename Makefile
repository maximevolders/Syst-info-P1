#make compile uniquement les fichiers afin de créer les exécutables
#make test lance le bash (et compile les fichiers si les exécutables n'existent pas)
#make clean supprime les exécutables

CC=gcc
CFLAGS=-W -Wall -pedantic

all: philo prod_cons lect_ecrv test_and_set test_and_test_and_set

test: philo prod_cons lect_ecrv
		./perf.sh

philo: philosophes.c
		$(CC) philosophes.c -pthread -o philo $(CFLAGS)

prod_cons: producteurs_consommateurs.c
		$(CC) producteurs_consommateurs.c -pthread -o prod_cons $(CFLAGS)

lect_ecrv: lecteurs_ecrivains.c
		$(CC) lecteurs_ecrivains.c -pthread -o lect_ecrv $(CFLAGS)
		
verrou: testlock
		./perf_tas.sh
	
test_and_set: test_and_set.c
		$(CC) test_and_set.c -pthread -o test_and_set $(CFLAGS)
		
test_and_test_and_set: verrou.c
		$(CC) verrou.c -pthread -o test_and_test_and_set $(CFLAGS)

clean:
		rm -rf philo lect_ecrv prod_cons test_and_set test_and_test_and_set
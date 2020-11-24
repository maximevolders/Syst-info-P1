#make compile uniquement les fichiers afin de créer les exécutables
#make test lance le bash (et compile les fichiers si les exécutables n'existent pas)
#make verrou lance les tests pour test_and_set, test_and_test_and_set, backoff_test_and_test_and_set et semaphore (et compile les fichiers si les exécutables n'existent pas)
#make clean supprime les exécutables

CC=gcc
CFLAGS=-Wall -std=c99 -pthread

all: philo_att_act philo_posix prod_cons_att_act prod_cons_posix lect_ecrv_att_act lect_ecrv_posix test_and_set test_verrous backoff_test_and_test_and_set


test: philo_att_act philo_posix prod_cons_att_act prod_cons_posix lect_ecrv_att_act lect_ecrv_posix
		./perf.sh

philo_att_act: philosophes_att_act.c test_and_test_and_set.c test_and_test_and_set.h
		$(CC) philosophes_att_act.c test_and_test_and_set.c -o philo_att_act $(CFLAGS)

philo_posix: philosophes_posix.c
		$(CC) philosophes_posix.c -o philo_posix $(CFLAGS)

prod_cons_att_act: producteurs_consommateurs_att_act.c semaphore.c test_and_test_and_set.c test_and_test_and_set.h semaphore.h
		$(CC) producteurs_consommateurs_att_act.c test_and_test_and_set.c semaphore.c -o prod_cons_att_act $(CFLAGS)

prod_cons_posix: producteurs_consommateurs_posix.c
		$(CC) producteurs_consommateurs_posix.c -o prod_cons_posix $(CFLAGS)

lect_ecrv_att_act: lecteurs_ecrivains_att_act.c test_and_test_and_set.c semaphore.c test_and_test_and_set.h semaphore.h
		$(CC) lecteurs_ecrivains_att_act.c test_and_test_and_set.c semaphore.c -o lect_ecrv_att_act $(CFLAGS)

lect_ecrv_posix: lecteurs_ecrivains_posix.c
		$(CC) lecteurs_ecrivains_posix.c -o lect_ecrv_posix $(CFLAGS)


verrou: test_verrous test_and_set backoff_test_and_test_and_set
		./perf_verrous.sh

test_verrous: test_verrous.c test_and_test_and_set.c test_and_test_and_set.h semaphore.c semaphore.h
		$(CC) test_verrous.c test_and_test_and_set.c semaphore.c -o test_verrous $(CFLAGS)

test_and_set: test_and_set.c
		$(CC) test_and_set.c -o test_and_set $(CFLAGS)

backoff_test_and_test_and_set: backoff_test_and_test_and_set.c
		$(CC) backoff_test_and_test_and_set.c -o backoff_test_and_test_and_set $(CFLAGS)


clean:
		rm -rf philo_att_act philo_posix prod_cons_att_act prod_cons_posix lect_ecrv_att_act lect_ecrv_posix test_and_set test_verrous backoff_test_and_test_and_set
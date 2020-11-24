#make compile uniquement les fichiers afin de créer les exécutables
#make test lance le bash (et compile les fichiers si les exécutables n'existent pas)
#make verrou lance les tests pour test_and_set et test_and_test_and_set (et compile les fichiers si les exécutables n'existent pas)
#make clean supprime les exécutables

CC=gcc
CFLAGS=-W -Wall -pedantic

all: philo_att_act philo_posix prod_cons_att_act prod_cons_posix lect_ecrv_att_act lect_ecrv_posix test_and_set test_and_test_and_set semaphore


test: philo_att_act philo_posix prod_cons_att_act prod_cons_posix lect_ecrv_att_act lect_ecrv_posix
		./perf.sh

philo_att_act: philosophes_att_act.c test_and_test_and_set.c
		$(CC) philosophes_att_act.c test_and_test_and_set.c -pthread -o philo_att_act $(CFLAGS)
		
philo_posix: philosophes_posix.c test_and_test_and_set.c
		$(CC) philosophes_posix.c test_and_test_and_set.c -pthread -o philo_posix $(CFLAGS)

prod_cons_att_act: producteurs_consommateurs_att_act.c semaphore.c test_and_test_and_set.c
		$(CC) producteurs_consommateurs_att_act.c test_and_test_and_set.c semaphore.c -pthread -o prod_cons_att_act $(CFLAGS)

prod_cons_posix: producteurs_consommateurs_posix.c semaphore.c test_and_test_and_set.c
		$(CC) producteurs_consommateurs_posix.c test_and_test_and_set.c semaphore.c -pthread -o prod_cons_posix $(CFLAGS)

lect_ecrv_att_act: lecteurs_ecrivains_att_act.c test_and_test_and_set.c semaphore.c
		$(CC) lecteurs_ecrivains_att_act.c test_and_test_and_set.c semaphore.c -pthread -o lect_ecrv_att_act $(CFLAGS)
		
lect_ecrv_posix: lecteurs_ecrivains_posix.c test_and_test_and_set.c semaphore.c
		$(CC) lecteurs_ecrivains_posix.c test_and_test_and_set.c semaphore.c -pthread -o lect_ecrv_posix $(CFLAGS)


verrou: test_and_set test_and_test_and_set
		./perf_tas.sh

test_and_set: test_and_set.c
		$(CC) test_and_set.c -pthread -o test_and_set $(CFLAGS)

test_and_test_and_set: test_and_test_and_set.c
		$(CC) test_and_test_and_set.c -pthread -o test_and_test_and_set $(CFLAGS)

semaphore: semaphore.c
		$(CC) semaphore.c -pthread -o semaphore $(CFLAGS)


clean:
		rm -rf philo lect_ecrv prod_cons test_and_set test_and_test_and_set semaphore
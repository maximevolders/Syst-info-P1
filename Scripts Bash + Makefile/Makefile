#make compile uniquement les fichiers afin de créer les exécutables
#make test lance le bash (et compile les fichiers si les exécutables n'existent pas)
#make verrou lance les tests pour test_and_set et test_and_test_and_set (et compile les fichiers si les exécutables n'existent pas)
#make clean supprime les exécutables

#si dans les fichiers test_and_set et test_and_test_and_set les tests et le main sont mit en commentaire, il faut les supprimer du 'all' sinon il y aura une erreur

CC=gcc
CFLAGS=-W -Wall -pedantic

all: philo prod_cons lect_ecrv test_and_set test_and_test_and_set semaphore


test: philo prod_cons lect_ecrv
		./perf.sh

philo: philosophes.c test_and_test_and_set.c
		$(CC) philosophes.c test_and_test_and_set.c -pthread -o philo $(CFLAGS)

prod_cons: producteurs_consommateurs.c semaphore.c test_and_test_and_set.c
		$(CC) producteurs_consommateurs.c test_and_test_and_set.c semaphore.c -pthread -o prod_cons $(CFLAGS)

lect_ecrv: lecteurs_ecrivains.c test_and_test_and_set.c semaphore.c
		$(CC) lecteurs_ecrivains.c test_and_test_and_set.c semaphore.c -pthread -o lect_ecrv $(CFLAGS)


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
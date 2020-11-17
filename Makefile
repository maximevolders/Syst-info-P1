#make compile uniquement les fichiers afin de créer les exécutables
#make test lance le bash (et compile les fichiers si les exécutables n'existent pas)
#make clean supprime les exécutables

CC=gcc
CFLAGS=-W -Wall -pedantic

all: philo prod_cons lect_ecrv

test: philo prod_cons lect_ecrv
		./perf.sh
		graph

philo: philosophes.c
		$(CC) philosophes.c -pthread -o philo $(CFLAGS)

prod_cons: producteurs_consommateurs.c
		$(CC) producteurs_consommateurs.c -pthread -o prod_cons $(CFLAGS)

lect_ecrv: lecteurs_ecrivains.c
		$(CC) lecteurs_ecrivains.c -pthread -o lect_ecrv $(CFLAGS)

clean:
		rm -rf philo lect_ecrv prod_cons
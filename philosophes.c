/**************************************
 * philosophes.c
 *
 * Programme du problème des philosophes
 * Dans le cadre du projet 1 du cours LINFO1225 - Systèmes informatiques
 *
 * Gauthier Arnold et Volders Maxime
 **************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define MAX 1000000

int PHILOSOPHES; // Nombre de philosophes

struct multArg{ // Structure pour pouvoir avoir accès aux baguettes globalement
    pthread_mutex_t* baguette;
};

struct multArg bag;

void error(int err, char *msg) {
    fprintf(stderr,"%s a retourné %d message d'erreur : %s\n",msg,err,strerror(errno));
    exit(EXIT_FAILURE);
}

// Fonction qui va faire penser et manger les philosophes 10.000 fois chacun.
void* philosophe( void* arg )
{

    int *id= (int *)arg;
    int left = *id;
    int right = (left + 1) % PHILOSOPHES;
    int i =0;
    while(i<MAX) { // Les philosophes doivent faire 10.000 cycles manger/penser
        // Philosophe pense
        if(left<right) { // Cette condition permet d'éviter d'avoir un deadlock
            pthread_mutex_lock((bag.baguette)+left);
            pthread_mutex_lock((bag.baguette)+right);
        }
        else {
            pthread_mutex_lock((bag.baguette)+right);
            pthread_mutex_lock((bag.baguette)+left);
        }
        // Philosophe mange
        pthread_mutex_unlock((bag.baguette)+left); // Philosophe libère ses baguettes
        pthread_mutex_unlock((bag.baguette)+right);
        i++;
    }
    return (NULL);
}

int main ( int argc, char *argv[])
{
    int i;
	if(argc != 2) return EXIT_FAILURE;
	PHILOSOPHES = atoi(argv[1]);
	if(PHILOSOPHES == 1) PHILOSOPHES++;
    pthread_mutex_t z[PHILOSOPHES]; // Mutex pour toutes les baguettes
    bag.baguette = z; // Stocke dans la struct pour que ce soit global

    int id[PHILOSOPHES];
    int err;
    pthread_t phil[PHILOSOPHES]; // Crée des threads pour chaque philosophe

    srand(getpid());

    for (i = 0; i < PHILOSOPHES; i++) // Donne un id a chaque philosophe
        id[i]=i;

    for (i = 0; i < PHILOSOPHES; i++) {// Initialise et Unlock les mutex
        err=pthread_mutex_init(bag.baguette+i, NULL);
        if(err!=0)
            error(err,"pthread_mutex_init");
    }

    for (i = 0; i < PHILOSOPHES; i++) { // On amorce les thread pour les philosophes
        err=pthread_create(&phil[i], NULL, philosophe, (void*)&(id[i]) );
        if(err!=0)
            error(err,"pthread_create");
    }

    for (i = 0; i < PHILOSOPHES; i++) { // On attend que chaque thread ait fini ses cycles
        pthread_join(phil[i], NULL);
        if(err!=0)
            error(err,"pthread_join");
    }

    for (i = 0; i < PHILOSOPHES; i++) { // Détruit les mutex à la fin des 10.000 cycles de chaque philosophe
        pthread_mutex_destroy(bag.baguette+i);
        if(err!=0)
            error(err,"pthread_mutex_destroy");
    }

    return (EXIT_SUCCESS);
}
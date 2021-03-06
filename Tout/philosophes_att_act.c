/**************************************
 * philosophes_att_act.c
 *
 * Programme du problème des philosophes avec les mutex par attente active
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
#include "test_and_test_and_set.h"

#define MAX 1000000

int PHILOSOPHES; // Nombre de philosophes
int nbag; //Nombre de baguettes

/* Structure pour pouvoir avoir accès aux baguettes globalement
 */
struct multArg{
    mut* baguette;
};

struct multArg bag;

void error(int err, char *msg) {
    fprintf(stderr,"%s a retourné %d message d'erreur : %s\n",msg,err,strerror(errno));
    exit(EXIT_FAILURE);
}

/* Fonction qui va faire penser et manger les philosophes 1.000.000 fois chacun.
 * Argument: Pointeur vers le tableau contenant l'ID du philosophe.
 */
void* philosophe( void* arg )
{

    int *id= (int *)arg;
    int left = *id;
    int right = (left + 1) % nbag;
    int i =0;
    while(i<MAX) { // Les philosophes doivent faire 1.000.000 cycles manger/penser
        // Philosophe pense
        if(left<right) { // Cette condition permet d'éviter d'avoir un deadlock
            mut_lock((bag.baguette)+left);
            mut_lock((bag.baguette)+right);

        }
        else {
            mut_lock((bag.baguette)+right);
            mut_lock((bag.baguette)+left);
        }
        // Philosophe mange
        // Philosophe libère ses baguettes
        mut_unlock((bag.baguette)+left);
        mut_unlock((bag.baguette)+right);
        i++;
    }
    return (NULL);
}

int main ( int argc, char *argv[])
{
    int i;
	if(argc != 2) return EXIT_FAILURE;
	PHILOSOPHES = atoi(argv[1]);
	nbag = PHILOSOPHES;
	if(PHILOSOPHES == 1){
	  nbag = 2;
	}
    // Mutex pour toutes les baguettes
	mut z[nbag];

    bag.baguette = z; // Stocke dans la struct pour que ce soit global

    int id[PHILOSOPHES];
    int err;
    pthread_t phil[PHILOSOPHES]; // Crée des threads pour chaque philosophe

    srand(getpid());

    for (i = 0; i < PHILOSOPHES; i++) // Donne un id a chaque philosophe
        id[i]=i;

    for (i = 0; i < nbag; i++) {// Initialise et Unlock les mutex
        mut_init(bag.baguette+i, 0);
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

    return (EXIT_SUCCESS);
}

/**************************************
 * test_and_set.c
 *
 * Programme du verrou test and set
 * Dans le cadre du projet 1 du cours LINFO1225 - Systèmes informatiques
 *
 * Gauthier Arnold et Volders Maxime
 **************************************/

#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

volatile int verrou=0;
int N;

//Message en cas d'erreur
void error(int err, char *msg) {
    fprintf(stderr,"%s a retourné %d message d'erreur : %s\n",msg,err,strerror(errno));
    exit(EXIT_FAILURE);
}

/* Verrou, empêche les autres thread d'aller plus loin tant que pas unlock */
void lock(){
	int test=1;
	while(test) {
        __asm__("movl $1, %%eax;"
            "xchgl %%eax, %0;"
            "movl %%eax, %1;"
        :"+m" (verrou), "=r" (test) /* paramètres de sortie */
        : /* paramètres d'entrée */
        :"%eax" /* registres modifiés */
        );
    }
}

//Déverouille, autorise un autre thread à accéder à sa section critique
void unlock(){
	verrou = 0;
}

//Méthode de test pour tester le verrou
void* test(){
	for(int i=0; i<6400/N; i++){
		lock();
		while(rand() > RAND_MAX/1000);
		unlock();
	}
	return (NULL);
}

int main(int argc, char *argv[]){
	int err;
	
	if(argc != 2) return (EXIT_FAILURE);
	N = atoi(argv[1]); // Nombre de threads
	
	pthread_t thread[N];
	
	for (int i=0; i<N; i++) { // On crée les threads
        err=pthread_create(&(thread[i]),NULL,test,NULL);
        if(err!=0)
            error(err,"pthread_create");
    }
	
	for(int i=0; i<N; i++) { // On attend que les threads se terminent
		err=pthread_join(thread[i],NULL);
        if(err!=0)
            error(err,"pthread_join");
	}
	return (EXIT_SUCCESS);
}
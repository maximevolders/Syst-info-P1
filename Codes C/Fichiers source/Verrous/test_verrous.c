/**************************************
 * test_verrous.c
 *
 * Programme de tests des différents verrous par attente active
 * Dans le cadre du projet 1 du cours LINFO1225 - Systèmes informatiques
 *
 * Gauthier Arnold et Volders Maxime
 **************************************/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* test semaphore */
// #include "semaphore.h"

/*test test_and_test_and_set */
#include "test_and_test_and_set.h"

int N;
mut mute;
//sema semp;

/* Message en cas d'erreur */
void error(int err, char *msg) {
    fprintf(stderr,"%s a retourné %d message d'erreur : %s\n",msg,err,strerror(errno));
    exit(EXIT_FAILURE);
}

void* test(){
	for(int i=0; i<6400/N; i++){
		// sema_wait(&semp); // test semaphore
		mut_lock(&mute); // test mutex
		while(rand() > RAND_MAX/1000);
		mut_unlock(&mute);
		// sema_post(&semp);
	}
	return (NULL);
} 

int main(int argc, char *argv[]){
	
	if(argc != 2) return (EXIT_FAILURE);
	N = atoi(argv[1]); // Nombre de threads

	pthread_t thread[N];
	
	// sema_init(&semp, 0);
	mut_init(&mute, 0);
	
	int err;
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
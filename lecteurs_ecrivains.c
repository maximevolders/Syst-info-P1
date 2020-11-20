/**************************************
 * lecteurs_ecrivains.c
 *
 * Programme du problème des lecteurs et écrivains
 * Dans le cadre du projet 1 du cours LINFO1225 - Systèmes informatiques
 *
 * Gauthier Arnold et Volders Maxime
 **************************************/

#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "test_and_test_and_set.h"
#include "semaphore.h"

#define MAX_LECT 2560
#define MAX_WRITE 640

/* POSIX */
pthread_mutex_t mutex_writecount;
pthread_mutex_t mutex_readcount;
pthread_mutex_t mutex_lect;
sem_t wsem;  // accès à la semaphore writer
sem_t rsem; // accès à la semaphore reader

/* ATTENTE ACTIVE */
struct mut mutex_writecount;
struct mut mutex_readcount;
struct mut mutex_lect;
struct sema wsem; // accès à la semaphore writer
struct sema rsem; // accès à la semaphore reader

int readcount=0; // nombre de readers
int writecount=0; // nombre d'écrivains
int nombre_lect=0; // nombre total de lectures
int nombre_write=0; // nombre total d'écritures

void error(int err, char *msg) {
    fprintf(stderr,"%s a retourné %d message d'erreur : %s\n",msg,err,strerror(errno));
    exit(EXIT_FAILURE);
}

void write_database(){
	while(rand() > RAND_MAX/10000);
}

void read_database(){
	while(rand() > RAND_MAX/10000);
}

void* writer(){
	while(nombre_write<MAX_WRITE){
		pthread_mutex_lock(&mutex_writecount); // POSIX
		mut_lock(&mutex_writecount); // ATTENTE ACTIVE
		
		writecount++;
		if(writecount == 1)
			// rsem N+1​​​​​
			sem_wait(&rsem); // POSIX
			sema_wait(&rsem); // ATTENTE ACTIVE
			
		pthread_mutex_unlock(&mutex_writecount); // POSIX
		mut_unlock(&mutex_writecount); // ATTENTE ACTIVE
		
		// WRITER SEM_WAIT
		sem_wait(&wsem); // POSIX
		sema_wait(&wsem); // ATTENTE ACTIVE
		
		// section critique, un seul writer à la fois
		if(nombre_write+writecount-1<MAX_WRITE){
			write_database();
			nombre_write++;
		}
		sem_post(&wsem); // POSIX
		sema_post(&wsem); // ATTENTE ACTIVE
		
		pthread_mutex_lock(&mutex_writecount); // POSIX
		mut_lock(&mutex_writecount); // ATTENTE ACTIVE
		
		writecount--;
		if(writecount == 0)
			sem_post(&rsem); // POSIX
			sema_post(&rsem); // ATTENTE ACTIVE
			
		pthread_mutex_unlock(&mutex_writecount); // POSIX
		mut_unlock(&mutex_writecount); // ATTENTE ACTIVE
	}
	return (NULL);
}

void* reader(){
	while(nombre_lect<MAX_LECT){
		// ne sera jamais > 1
		sem_wait(&rsem); // POSIX
		sema_wait(&rsem); // ATTENTE ACTIVE
		
		
		pthread_mutex_lock(&mutex_readcount); // POSIX
		mut_lock(&mutex_readcount); // ATTENTE ACTIVE
		
		// section critique
		readcount++;
		if(readcount==1) // arrivée du premier reader
			sem_wait(&wsem); // POSIX
			sema_wait(&wsem); // ATTENTE ACTIVE
			
		pthread_mutex_unlock(&mutex_readcount); // POSIX
		mut_unlock(&mutex_readcount); // ATTENTE ACTIVE
		
		sem_post(&rsem); // POSIX
		sema_post(&rsem); // ATTENTE ACTIVE
		
		if(nombre_lect+readcount-1<MAX_LECT && nombre_write>0){
			// 1 reader rsem 1
			read_database();
			
			pthread_mutex_lock(&mutex_lect); // POSIX
			mut_lock(&mutex_lect); // ATTENTE ACTIVE
			
			// section critique
			nombre_lect++;
			pthread_mutex_unlock(&mutex_lect); // POSIX
			mut_unlock(&mutex_lect); // ATTENTE ACTIVE
		}
		pthread_mutex_lock(&mutex_readcount); // POSIX
		mut_lock(&mutex_readcount); // ATTENTE ACTIVE
		
		// section critique
		readcount--;
		if(readcount==0) // départ du dernier reader
			sem_post(&wsem); // POSIX
			sema_post(&wsem); // ATTENTE ACTIVE
		
		pthread_mutex_unlock(&mutex_readcount); // POSIX
		mut_unlock(&mutex_readcount); // ATTENTE ACTIVE
		//process_data();
	}
	return (NULL);
}

int main(int argc, char *argv[]){
	int err;
	
	if(argc != 2) return EXIT_FAILURE;
	
	int ecrivains = atoi(argv[1])/2; // Nombre de ecrivains
	
	int lecteurs = atoi(argv[1])/2; // Nombre de lecteurs
	if(atoi(argv[1])%2) lecteurs++;
	
	/* POSIX */
	pthread_mutex_init(&mutex_writecount,NULL);
	pthread_mutex_init(&mutex_readcount,NULL);
	pthread_mutex_init(&mutex_lect,NULL);
	sem_init(&wsem, 0, 1);
	sem_init(&rsem, 0, 1);
	
	/* ATTENTE ACTIVE */
	mut_init(&mutex_writecount);
	mut_init(&mutex_readcount);
	mut_init(&mutex_lect);
	sema_init(&wsem, 1);
	sema_init(&rsem, 1);
	
	pthread_t lect[lecteurs]; // Un thread par lecteur
	pthread_t ecrv[ecrivains]; // Un thread par écrivain
	
	for(int i=0;i<ecrivains;i++) { // On crée les threads écrivains
		err=pthread_create(&(ecrv[i]),NULL,writer,NULL);
        if(err!=0)
            error(err,"pthread_create");
	}
	
	for(int i=0;i<lecteurs;i++) { // On crée les threads lecteurs
		err=pthread_create(&(lect[i]),NULL,reader,NULL);
        if(err!=0)
            error(err,"pthread_create");
	}

	for(int i=0;i<ecrivains;i++) { // On attend que les threads écrivains se terminent
		err=pthread_join(ecrv[i],NULL);
        if(err!=0)
            error(err,"pthread_join");
	}
	
	for(int i=0;i<lecteurs;i++) { // On attend que les threads lecteurs se terminent
		err=pthread_join(lect[i],NULL);
        if(err!=0)
            error(err,"pthread_join");
	}

	return EXIT_SUCCESS;
}
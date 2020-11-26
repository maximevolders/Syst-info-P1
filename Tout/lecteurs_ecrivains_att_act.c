/**************************************
 * lecteurs_ecrivains.c
 *
 * Programme du problème des lecteurs et écrivains
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
#include "semaphore.h"
#include "test_and_test_and_set.h"

#define MAX_LECT 2560
#define MAX_WRITE 640

mut mutex_writecount;
mut mutex_readcount;
mut mutex_lect;
sema wsem; // accès à la semaphore writer
sema rsem; // accès à la semaphore reader

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
		mut_lock(&mutex_writecount);
		
		writecount++;
		if(writecount == 1){
			sema_wait(&rsem);
		}

		mut_unlock(&mutex_writecount);

		sema_wait(&wsem);
		
		// section critique, un seul writer à la fois
		if(nombre_write+writecount-1<MAX_WRITE){
			write_database();
			nombre_write++;
		}

		sema_post(&wsem);

		mut_lock(&mutex_writecount);
		
		writecount--;
		if(writecount == 0){
			sema_post(&rsem);
		}

		mut_unlock(&mutex_writecount);
	}
	return (NULL);
}

void* reader(){
	while(nombre_lect<MAX_LECT){
		// ne sera jamais > 1
		sema_wait(&rsem);

		mut_lock(&mutex_readcount);
		
		// section critique
		readcount++;
		if(readcount==1){ // arrivée du premier reader
			sema_wait(&wsem);
		}

		mut_unlock(&mutex_readcount);

		sema_post(&rsem);
		
		if(nombre_lect+readcount-1<MAX_LECT){
			// 1 reader rsem 1
			read_database();

			mut_lock(&mutex_lect);
			
			// section critique
			nombre_lect++;
			mut_unlock(&mutex_lect);
		}
		mut_lock(&mutex_readcount);
		
		// section critique
		readcount--;
		if(readcount==0){ // départ du dernier reader
			sema_post(&wsem);
		}
		mut_unlock(&mutex_readcount);
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

	mut_init(&mutex_writecount, 0);
	mut_init(&mutex_readcount, 0);
	mut_init(&mutex_lect, 0);
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
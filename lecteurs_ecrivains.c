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

#define MAX_LECT 2560
#define MAX_WRITE 640

pthread_mutex_t mutex_writecount;
pthread_mutex_t mutex_readcount;
pthread_mutex_t mutex_lect;
sem_t wsem;  // accès à la semaphore writer
sem_t rsem; // accès à la semaphore reader
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
		pthread_mutex_lock(&mutex_writecount);
		writecount++;
		if(writecount == 1)
			sem_wait(&rsem); // rsem N+1​​​​​
			
		pthread_mutex_unlock(&mutex_writecount);
		
		sem_wait(&wsem); // WRITER SEM_WAIT
		// section critique, un seul writer à la fois
		if(nombre_write+writecount-1<MAX_WRITE){
			write_database();
			nombre_write++;
		}
		sem_post(&wsem);
		
		pthread_mutex_lock(&mutex_writecount);
		writecount--;
		if(writecount == 0)
			sem_post(&rsem);
			
		pthread_mutex_unlock(&mutex_writecount);
	}
	return (NULL);
}

void* reader(){
	while(nombre_lect<MAX_LECT){
		sem_wait(&rsem); // ne sera jamais > 1
		pthread_mutex_lock(&mutex_readcount); // Pq y a 2 mutex? et une sémaphore?
		// section critique
		readcount++;
		if(readcount==1) // arrivée du premier reader
			sem_wait(&wsem);
			
		pthread_mutex_unlock(&mutex_readcount);
		sem_post(&rsem);
		
		if(nombre_lect+readcount-1<MAX_LECT && nombre_write>0){
			// 1 reader rsem 1
			read_database();
			
			pthread_mutex_lock(&mutex_lect);
			// section critique
			nombre_lect++;
			pthread_mutex_unlock(&mutex_lect);
		}
		pthread_mutex_lock(&mutex_readcount);
		// section critique
		readcount--;
		if(readcount==0) // départ du dernier reader
			sem_post(&wsem);
		
		pthread_mutex_unlock(&mutex_readcount);
		//process_data();
	}
	return (NULL);
}

int main(int argc, char *argv[]){
	int err;
	
	if(argc != 3) return EXIT_FAILURE;
	
	int ecrivains = atoi(argv[1]); // Nombre de ecrivains
	if(ecrivains%2) ecrivains++;
	
	int lecteurs = atoi(argv[2]); // Nombre de lecteurs
	if(lecteurs%2) lecteurs++;
	
	pthread_mutex_init(&mutex_writecount,NULL);
	pthread_mutex_init(&mutex_readcount,NULL);
	pthread_mutex_init(&mutex_lect,NULL);
	sem_init(&wsem, 0, 1);
	sem_init(&rsem, 0, 1);
	
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
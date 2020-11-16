/**************************************
 * producteurs_consommateurs.c
 *
 * Programme du problème des producteurs et consommateurs
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

#define N 8 // La taille du buffer
#define MAX 1024 // Le nombre max d'éléments à produire/consommer

int buffer[N]; // On initialise le buffer (tous ses éléments valent 0)
pthread_mutex_t mutex;
sem_t empty;
sem_t full;
int elem_prod=0; // Le nombre total d'éléments produits
int elem_cons=0; // Le nombre total d'éléments consommés

void error(int err, char *msg) {
    fprintf(stderr,"%s a retourné %d message d'erreur : %s\n",msg,err,strerror(errno));
    exit(EXIT_FAILURE);
}

// On produit un nouvel élément grâce à la fonction rand. Si rand retourne 0, on reproduit un élément.
// Return: le nouvel élément à insérer dans la liste.
int produce_item(){
	int rando = rand();
	if(rando == 0)
		produce_item();
	return rando;
}

// On insère un élément dans le buffer. Les espaces vides du buffer sont égaux à 0.
// Argument: l'élément à insérer
void insert_item(int item){
	for(int i=0; i<N; i++){
		if(buffer[i] == 0){
			buffer[i] = item;
			return;
		}
	}
	error(1, "Élément non inséré!"); // Ne devrait jamais être imprimé
}


// On supprime un élément du buffer. L'espace libéré est mis à 0.
// Return: l'élément supprimé du buffer
void remove_item(){
	for(int i=0; i<N; i++){
		if(buffer[i] != 0){
			buffer[i] = 0;
			return;
		}
	}
	error(1, "Pas d'élément enlevé de la liste!"); // Ne devrait jamais être imprimé
}

// Producteur
void* producer(){
	int item;
	while(elem_prod<MAX){ // Tant qu'on a pas atteint le nombre max d'éléments à produire
		item = produce_item();
		sem_wait(&empty); // Attente d'une place libre

		pthread_mutex_lock(&mutex); // Section critique
		if(elem_prod<MAX){ // Si on a produit moins que le nombre max d'éléments
			insert_item(item);
			elem_prod++;
			
			pthread_mutex_unlock(&mutex); // Fin section critique
		
			sem_post(&full); // Il y a une place remplie en plus
			
			if(elem_prod >= MAX)
				sem_post(&empty); // Afin de ne bloquer aucun producteur

			while(rand() > RAND_MAX/10000);
		} else { // Si on a produit le nombre max d'éléments, on libère juste le mutex
			pthread_mutex_unlock(&mutex);
			sem_post(&empty); // Afin de ne bloquer aucun producteur
		}
	}
	return (NULL);
}

// Consommateur
void* consumer(){
	while(elem_cons<MAX){ // Tant qu'on a pas consommé le nombre max d'éléments
		sem_wait(&full); // Attente d'une place remplie
		
		pthread_mutex_lock(&mutex); // Section critique
		if(elem_cons<MAX){ // Si on a consommé moins que le nombre max d'éléments
			remove_item();
			elem_cons++;
			
			pthread_mutex_unlock(&mutex); // Fin section critique
		
			sem_post(&empty); // Il y a une place libre en plus
			
			if(elem_cons >= MAX)
				sem_post(&full);
			
			while(rand() > RAND_MAX/10000);
		} else { // Si on a consommé le nombre max d'éléments, on libère juste le mutex
			pthread_mutex_unlock(&mutex);
			sem_post(&full); // Afin de ne bloquer aucun consommateur
		}
	}
	return (NULL);
}

int main(int argc, char *argv[]){
	int err;
	
	if(argc != 3) return EXIT_FAILURE;
	
	int producteurs = atoi(argv[1]); // Nombre de producteurs
	if(producteurs%2) producteurs++;
	
	int consommateurs = atoi(argv[2]); // Nombre de consommateurs
	if(consommateurs%2) consommateurs++;
	
	pthread_mutex_init(&mutex, NULL);
	sem_init(&empty, 0 , N);  // buffer vide
	sem_init(&full, 0 , 0);   // buffer vide
	
	pthread_t cons[consommateurs]; // Un thread par producteur
	pthread_t prod[producteurs]; // Un thread par consommateur

	for(int i=0;i<producteurs;i++) { // On crée les threads producteurs
		err=pthread_create(&(prod[i]),NULL,producer,NULL);
		if(err!=0)
            error(err,"pthread_create");
	}
	
	for(int i=0;i<consommateurs;i++) { // On crée les threads consommateurs
		err=pthread_create(&(cons[i]),NULL,consumer,NULL);
        if(err!=0)
            error(err,"pthread_create");
	}

	for(int i=0;i<producteurs;i++) { // On attend que les threads producteurs se terminent
		err=pthread_join(prod[i],NULL);
        if(err!=0)
            error(err,"pthread_join");
	}
	
	for(int i=0;i<consommateurs;i++) { // On attend que les threads consommateurs se terminent
		err=pthread_join(cons[i],NULL);
        if(err!=0)
            error(err,"pthread_join");
	}
	
	pthread_mutex_destroy(&mutex); // Libération de la mémoire
	sem_destroy(&empty);
	sem_destroy(&full);
	
	return EXIT_SUCCESS;
}

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
#include "semaphore.h"
#include "test_and_test_and_set.h"

#define N 8 // La taille du buffer
#define MAX 1024 // Le nombre max d'éléments à produire/consommer

int buffer[N]; // On initialise le buffer (tous ses éléments valent 0)

struct mut mutex;
struct sema empty;
struct sema full;

int elem_prod=0; // Le nombre total d'éléments produits
int elem_cons=0; // Le nombre total d'éléments consommés

void error(int err, char *msg) {
    fprintf(stderr,"%s a retourné %d message d'erreur : %s\n",msg,err,strerror(errno));
    exit(EXIT_FAILURE);
}

/* On produit un nouvel élément grâce à la fonction rand. Si rand retourne 0, on reproduit un élément.
 * Return: le nouvel élément à insérer dans la liste.
 * */
int produce_item(){
	int rando = rand();
	if(rando == 0)
		produce_item();
	return rando;
}

/* On insère un élément dans le buffer. Les espaces vides du buffer sont égaux à 0.
 * Argument: l'élément à insérer
 */
void insert_item(int item){
	for(int i=0; i<N; i++){
		if(buffer[i] == 0){
			buffer[i] = item;
			return;
		}
	}
	error(1, "Élément non inséré!"); // Ne devrait jamais être imprimé
}


/*On supprime un élément du buffer. L'espace libéré est mis à 0.
 * Return: l'élément supprimé du buffer
 * */
void remove_item(){
	for(int i=0; i<N; i++){
		if(buffer[i] != 0){
			buffer[i] = 0;
			return;
		}
	}
	error(1, "Pas d'élément enlevé de la liste!"); // Ne devrait jamais être imprimé
}

/*Producteur
 */
void* producer(){
	int item;
	while(elem_prod<MAX){ // Tant qu'on a pas atteint le nombre max d'éléments à produire
		item = produce_item();
		
		// Attente d'une place libre
		sema_wait(&empty);
		
		// Section critique
		mut_lock(&mutex);
		
		if(elem_prod<MAX){ // Si on a produit moins que le nombre max d'éléments
			insert_item(item);
			elem_prod++;
			
			// Fin section critique
			mut_unlock(&mutex);
		
			// Il y a une place remplie en plus
			sema_post(&full);
			
			if(elem_prod >= MAX)
				// Afin de ne bloquer aucun producteur
				sema_post(&empty);

			while(rand() > RAND_MAX/10000);
		} else { // Si on a produit le nombre max d'éléments, on libère juste le mutex
			mut_unlock(&mutex);
			
			// Afin de ne bloquer aucun producteur
			sema_post(&empty);
		}
	}
	return (NULL);
}

/*Consommateur
 */
void* consumer(){
	while(elem_cons<MAX){ // Tant qu'on a pas consommé le nombre max d'éléments
		// Attente d'une place remplie
		sema_wait(&full);
		
		// Section critique
		mut_lock(&mutex);
		
		if(elem_cons<MAX){ // Si on a consommé moins que le nombre max d'éléments
			remove_item();
			elem_cons++;
			
			// Fin section critique
			mut_unlock(&mutex);
		
			// Il y a une place libre en plus
			sema_post(&empty);
			
			if(elem_cons >= MAX)
				sema_post(&full);
			
			while(rand() > RAND_MAX/10000);
		} else {
		    // Si on a consommé le nombre max d'éléments, on libère juste le mutex
			mut_unlock(&mutex);
			
			// Afin de ne bloquer aucun consommateur
			sema_post(&full);
		}
	}
	return (NULL);
}

int main(int argc, char *argv[]){
	int err;
	
	if(argc != 2) return EXIT_FAILURE;
	
	int producteurs = atoi(argv[1])/2; // Nombre de producteurs
	if(producteurs == 0) producteurs++;
	
	int consommateurs = atoi(argv[1])/2; // Nombre de consommateurs
	if(atoi(argv[1])%2) consommateurs++;

	mut_init(&mutex);
	sema_init(&empty, N); // buffer vide
	sema_init(&full, 0); // buffer vide
	
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

	
	printf("%d, %d\n", elem_prod, elem_cons);
	
	return EXIT_SUCCESS;
}

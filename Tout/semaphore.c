/**************************************
 * semaphore.c
 *
 * Programme des semaphores par attente active
 * Dans le cadre du projet 1 du cours LINFO1225 - Systèmes informatiques
 *
 * Gauthier Arnold et Volders Maxime
 **************************************/
 
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

// Structure définie dans le fichier semaphore.h
#include "semaphore.h"

/* Fonction d'initialisation de la sémaphore. Met les 2 verrous à 0 (libre) et définie la valeur de la sémaphore.
 * Arguments: pointeur vers la sémaphore à initialiser et la valeur de la sémaphore
 * Return: 0 en cas de succès
 */
void sema_init(sema *s, unsigned int value){
	s->val=value;
	mut_init(&(s->semlock), 1);
	mut_init(&(s->count), 0);
}

/* Fonction de wait de la sémaphore.
 * Arguments: pointeur vers la sémaphore.
 */
void sema_wait(sema *s){
	mut_lock(&(s->count)); // début section critique
	s->val = (s->val)-1;

	if((s->val)<0){ // On lock la sémaphore si la valeur est < 0
		mut_unlock(&(s->count)); // fin de section critique
		mut_lock(&(s->semlock)); // Ajout de thread dans la queue
	}
	mut_unlock(&(s->count)); // fin de section critique
}

/* Fonction de post de la sémaphore.
 * Arguments: pointeur vers la sémaphore.
 */
void sema_post(sema *s){
	mut_lock(&(s->count)); // début de section critique
	s->val = (s->val)+1;
	
	if((s->val)<=0){
		mut_unlock(&(s->semlock)); // On unlock la sémaphore, permettant a un thread dans la queue de continuer son exécution
	} else {
		mut_unlock(&(s->count)); // fin de section critique
	}
}

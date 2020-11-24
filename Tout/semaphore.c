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
	(s->semlock) = 0;
	(s->ver) = 0;
}

/* Fonction test_and_set
 * Arguments: pointeur vers la valeur de verrou à tester
 * Return: 1 si le verrou est lock, 0 s'il est unlock
 */
int sema_testAndSet(volatile int *verrou){
	int test=1;
		__asm__("movl $1, %%eax;"
		"xchgl %%eax, %0;"
		"movl %%eax, %1;"
		:"+m" (*verrou), "=r" (test) /* paramètres de sortie */
		: /* paramètres d'entrée */
		:"%eax" /* registres modifiés */
		);
	return test;
}

/* Fonction de verrouillage.
 * Arguments: pointeur vers la valeur de verrou à tester
 */
void sema_lock(volatile int *verrou){
	do{
		while(*verrou == 1);
	} while(sema_testAndSet(verrou) == 1);
}

/* Fonction de déverrouillage.
 * Arguments: pointeur vers la valeur de verrou à déverouiller
 */
void sema_unlock(volatile int *verrou){
	*verrou = 0;
}

/* Fonction de wait de la sémaphore.
 * Arguments: pointeur vers la sémaphore.
 */
void sema_wait(sema *s){
	sema_lock(&(s->semlock)); // début section critique
	s->val = (s->val)-1;

	if((s->val)<0){ // On lock la sémaphore si la valeur est <= 0 (si val = 1, le premier lock va passer et verouiller les autres)
		sema_unlock(&(s->semlock)); // fin de section critique
		s->ver = 1;
		sema_lock(&(s->ver)); // Ajout de thread dans la queue
	} else {
		sema_unlock(&(s->semlock)); // fin de section critique
	}
}

/* Fonction de post de la sémaphore.
 * Arguments: pointeur vers la sémaphore.
 */
void sema_post(sema *s){
	sema_lock(&(s->semlock)); // début de section critique
	s->val = (s->val)+1;
	
	if((s->val)<=0){
		sema_unlock(&(s->ver)); // On unlock la sémaphore, permettant a un thread dans la queue de continuer son exécution
	}
	sema_unlock(&(s->semlock)); // fin de section critique
}

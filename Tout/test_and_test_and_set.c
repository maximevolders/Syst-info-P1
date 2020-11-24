/**************************************
 * test_and_test_and_set.c
 *
 * Programme du verrou test-and-test-and-set
 * Dans le cadre du projet 1 du cours LINFO1225 - Systèmes informatiques
 *
 * Gauthier Arnold et Volders Maxime
 **************************************/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

// Structure définie dans le fichier test_and_test_and_set.h
#include "test_and_test_and_set.h"

void mut_init(mut* mu){
	mu->ver=0;
}

int mut_testAndSet(mut* mu){
	int test=1;
		__asm__("movl $1, %%eax;"
		"xchgl %%eax, %0;"
		"movl %%eax, %1;"
		:"+m" (mu->ver), "=r" (test) /* paramètres de sortie */
		: /* paramètres d'entrée */
		:"%eax" /* registres modifiés */
		);
	return test;
}

void mut_lock(mut* mu){
	do{
		while(mu->ver == 1);
	} while(mut_testAndSet(mu) == 1);
}

void mut_unlock(mut *mu){
	mu->ver = 0;
}
/**************************************
 * test_and_test_and_set.h
 *
 * Header du fichier test_and_test_and_set.c
 * Dans le cadre du projet 1 du cours LINFO1225 - Systèmes informatiques
 *
 * Gauthier Arnold et Volders Maxime
 **************************************/

#ifndef TATAS
#define TATAS

typedef struct mut{
	volatile int ver;
}mut;

void mut_init(mut* mu, unsigned int val);

int mut_testAndSet(mut* mu);

void mut_lock(mut* mu);

void mut_unlock(mut* mu);

#endif
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

struct sema{
	volatile int val; // Valeur de la sémaphore
	volatile int ver; // Verrou de la sémaphore, bloquant les threads lors de l'appel wait()
	volatile int semlock; // Verrou dans la sémaphore, verrouillant les sections critiques de l'implémentation de notre sémaphore
};

int sema_init(struct sema *s, unsigned int value);
int sema_testAndSet(volatile int *verrou);
void sema_lock(volatile int *verrou);
void sema_unlock(volatile int *verrou);
void sema_wait(struct sema *s);
void sema_post(struct sema *s);
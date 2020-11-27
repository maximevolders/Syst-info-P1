#ifndef SEMACT
#define SEMACT

#include "test_and_test_and_set.h"

typedef struct sema{
	volatile int val; // Valeur de la sémaphore
	mut count;
	mut semlock; // Verrou de la sémaphore, bloquant les threads lors de l'appel wait()
}sema;

void sema_init(sema *s, unsigned int value);

void sema_wait(sema *s);

void sema_post(sema *s);

#endif
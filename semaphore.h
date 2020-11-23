#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

struct sema{
	volatile int val;
	volatile int verrou;
	volatile int semlock;
};

int sema_init(struct sema *s, unsigned int value);
int sema_testAndSet(volatile int *verrou);
void sema_lock(volatile int *verrou);
void sema_unlock(volatile int *verrou);
void sema_wait(struct sema *s);
void sema_post(struct sema *s);
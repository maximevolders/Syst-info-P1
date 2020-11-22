#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

struct sema{
	volatile int val;
	volatile int verrou;
};

int sema_init(struct sema *s, unsigned int value);
int sema_testAndSet(struct sema *s);
void sema_lock(struct sema *s);
void sema_unlock(struct sema *s);
void sema_wait(struct sema *s);
void sema_post(struct sema *s);
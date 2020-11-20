#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

struct mut{
	volatile int verrou;
};

int mut_init(struct mut *mu);
int mut_testAndSet(struct mut *mu);
void mut_lock(struct mut *mu);
void mut_unlock(struct mut *mu);
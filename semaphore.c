#include "semaphore.h"

int sema_init(struct sema *s, unsigned int value){
	s->val=value;
	s->verrou = 0;
	s->semlock = 0;
	return 0;
}

int sema_testAndSet(volatile int *verrou){
	int test=1;
		asm("movl $1, %%eax;"
		"xchgl %%eax, %0;"
		"movl %%eax, %1;"
		:"+m" (*verrou), "=r" (test) /* paramètres de sortie */
		: /* paramètres d'entrée */
		:"%eax" /* registres modifiés */
		);
	return test;
}

void sema_lock(volatile int *verrou){
	do{
		while(*verrou == 1);
	} while(sema_testAndSet(verrou) == 1);
}

void sema_unlock(volatile int *verrou){
	*verrou = 0;
}

void sema_wait(struct sema *s){
	if((s->val)<=1){
		sema_lock(&(s->verrou));
	}
	sema_lock(&(s->semlock));
	s->val = (s->val)-1;
	sema_unlock(&(s->semlock));
}

void sema_post(struct sema *s){
	sema_lock(&(s->semlock));
	s->val = (s->val)+1;
	sema_unlock(&(s->verrou));
	sema_unlock(&(s->semlock));
}
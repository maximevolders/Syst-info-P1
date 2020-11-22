#include "semaphore.h"

int sema_init(struct sema *s, unsigned int value){
	s->val=value;
	s->verrou = 1;
	return 0;
}

int sema_testAndSet(struct sema *s){
	int test=1;
		asm("movl $1, %%eax;"
		"xchgl %%eax, %0;"
		"movl %%eax, %1;"
		:"+m" (s->verrou), "=r" (test) /* paramètres de sortie */
		: /* paramètres d'entrée */
		:"%eax" /* registres modifiés */
		);
	return test;
}

void sema_lock(struct sema *s){
	do{
		while(s->verrou == 1);
	} while(sema_testAndSet(s) == 1);
}

void sema_unlock(struct sema *s){
	s->verrou = 0;
}

void sema_wait(struct sema *s){
	s->val = (s->val)-1;
	if((s->val)<=0)
		sema_lock(s);
}

void sema_post(struct sema *s){
	s->val = (s->val)+1;
	if((s->val)>0)
		sema_unlock(s);
}
#include "semaphore.h"

int N;

struct sema mute;
struct sema mute2;

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
	if((s->val)<0)
		sema_lock(s);
}

void sema_post(struct sema *s){
	s->val = (s->val)+1;
	if((s->val)<=0)
		sema_unlock(s);
}




void* test1(){
	for(int i=0; i<64/N; i++){
		sema_wait(&mute);
		int j=0;
		while(rand() > RAND_MAX/1000);
		while(j<9){
			printf("%d", j);
			j++;
		}
		printf("\n");
		sema_post(&mute);
	}
	return (NULL);
}

void* test2(){
	for(int i=0; i<64/N; i++){
		sema_wait(&mute);
		int j=0;
		while(rand() > RAND_MAX/1000);
		while(j>-9){
			printf("%d", j);
			j--;
		}
		printf("\n");
		sema_post(&mute);
	}
	return (NULL);
}
/* POUR LES TESTS */
/*
int main(int argc, char *argv[]){
	int err;
	
	if(argc != 2) return (EXIT_FAILURE);
	N = atoi(argv[1]); // Nombre de threads

	pthread_t thread[N];
	
	sema_init(&mute, 0);
	sema_init(&mute2, 0);
	
    for (int i=0; i<N; i++) { // On crée les threads
		if(i<N/2)
			err=pthread_create(&(thread[i]),NULL,test1,NULL);
		else
			err=pthread_create(&(thread[i]),NULL,test2,NULL);
    }
	
	for(int i=0; i<N; i++) { // On attend que les threads se terminent
		err=pthread_join(thread[i],NULL);
	} 
	return (EXIT_SUCCESS);
} */
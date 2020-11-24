#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

typedef struct mut{
	volatile int ver;
}mut;

int N;
mut mute;

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


void* test(){
	for(int i=0; i<6400/N; i++){
		mut_lock(&mute);
		while(rand() > RAND_MAX/1000);
		mut_unlock(&mute);
	}
	return (NULL);
} 

int main(int argc, char *argv[]){
	
	if(argc != 2) return (EXIT_FAILURE);
	N = atoi(argv[1]); // Nombre de threads

	pthread_t thread[N];
	
	mut_init(&mute);
	
    for (int i=0; i<N; i++) { // On crée les threads
        pthread_create(&(thread[i]),NULL,test,NULL);
        
    }

    for(int i=0; i<N; i++) { // On attend que les threads se terminent
      pthread_join(thread[i],NULL);
    }
    return (EXIT_SUCCESS);
}

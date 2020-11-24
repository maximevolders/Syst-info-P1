#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MIN_SLEEP 2 // attente minimale en micro-secondes
#define MAX_SLEEP 13000 // attente maximale en micro-secondes

typedef struct mut{
	volatile int ver;
}mut;

int N;
mut mute;

/* Message en cas d'erreur */
void error(int err, char *msg) {
    fprintf(stderr,"%s a retourné %d message d'erreur : %s\n",msg,err,strerror(errno));
    exit(EXIT_FAILURE);
}

void mut_init(mut *mu){
	mu->ver=0;
}

int mut_testAndSet(mut *mu){
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

void mut_lock(mut *mu){
	do{
		unsigned int time_sleep = MIN_SLEEP; // temps de sleep en micro-secondes
		struct timespec req;
		while(mu->ver == 1){
			req.tv_nsec = (time_sleep-rand()%(time_sleep/2))*1000; // sleep en nano-secondes avec un part de random
			nanosleep(&req,NULL); // sleep en nano-secondes
			if(2*time_sleep <= MAX_SLEEP) 
				time_sleep *=2;
			else
				time_sleep = MAX_SLEEP;
		};
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
	
	int err;
	for (int i=0; i<N; i++) { // On crée les threads
        err=pthread_create(&(thread[i]),NULL,test,NULL);
        if(err!=0)
            error(err,"pthread_create");
    }
	
	for(int i=0; i<N; i++) { // On attend que les threads se terminent
		err=pthread_join(thread[i],NULL);
        if(err!=0)
            error(err,"pthread_join");
	}
	return (EXIT_SUCCESS);
}

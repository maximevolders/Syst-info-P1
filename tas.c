#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

volatile int verrou=0;
int N;

void error(int err, char *msg) {
    fprintf(stderr,"%s a retourné %d message d'erreur : %s\n",msg,err,strerror(errno));
    exit(EXIT_FAILURE);
}

void lock(){
	do{
		asm("movl %1, %%eax;"
		"xchgl %0, %%eax;"
		"movl %%eax, %1;"
		:"+r" (verrou), "+r" (test)
		);
	} while(test == 1);
}

void unlock(){
	asm("movl $0, %%eax;"
		"xchgl %%eax, %0;"
		:"=&r"(verrou));
}

void* test(){
	for(int i=0; i<6400/N; i++){
		lock();
		while(rand() > RAND_MAX/1000);
		unlock();
	}
	return (NULL);
}

int main(int argc, char *argv[]){
	int err;
	
	if(argc != 2) return (EXIT_FAILURE);
	N = atoi(argv[1]); // Nombre de threads
	
	pthread_t thread[N];
	
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
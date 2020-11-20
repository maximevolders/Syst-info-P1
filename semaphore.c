#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

volatile int verrou=0;
int N;
struct sema{
	int val;
};
struct sema semaphore;

void error(int err, char *msg) {
    fprintf(stderr,"%s a retourné %d message d'erreur : %s\n",msg,err,strerror(errno));
    exit(EXIT_FAILURE);
}

int init(struct sema sem, unsigned int value){
	printf("Dans init\n");
	sem.val=value;
	return 0;
}

int testAndSet(){
	int test=1;
		asm("movl $1, %%eax;"
		"xchgl %%eax, %0;"
		"movl %%eax, %1;"
		:"+m" (verrou), "=r" (test) /* paramètres de sortie */
		: /* paramètres d'entrée */
		:"%eax" /* registres modifiés */
		);
	return test;
}

void lock(){
	do{
		while(verrou == 1);
	} while(testAndSet() == 1);
}

void unlock(){
	verrou = 0;
}

void wait(struct sema *s){
	s->val = (s->val)-1;
	if((s->val)<0)
		lock();
}

void post(struct sema *s){
	s->val = (s->val)+1;
	if((s->val)<=0)
		unlock();
}

void* test(){
	for(int i=0; i<6400/N; i++){
		wait(&semaphore);
		int j=0;
		while(rand() > RAND_MAX/1000);
		while(j<9){
			printf("%d", j);
			j++;
		}
		printf("\n");
		post(&semaphore);
	}
	return (NULL);
}

int main(int argc, char *argv[]){
	int err;
	
	if(argc != 2) return (EXIT_FAILURE);
	N = atoi(argv[1]); // Nombre de threads

	pthread_t thread[N];
	printf("Avant init\n");
	err=init(semaphore, 0);
	printf("Après init\n");
	
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
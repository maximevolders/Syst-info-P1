#include "test_and_test_and_set.h"

int N;

struct mut mute;

int mut_init(struct mut *mu){
	mu->verrou=0;
	return 0;
}

int mut_testAndSet(struct mut *mu){
	int test=1;
		asm("movl $1, %%eax;"
		"xchgl %%eax, %0;"
		"movl %%eax, %1;"
		:"+m" (mu->verrou), "=r" (test) /* paramètres de sortie */
		: /* paramètres d'entrée */
		:"%eax" /* registres modifiés */
		);
	return test;
}

void mut_lock(struct mut *mu){
	do{
		while(mu->verrou == 1);
	} while(mut_testAndSet(mu) == 1);
}

void mut_unlock(struct mut *mu){
	mu->verrou = 0;
}

void* test(){
	for(int i=0; i<6400/N; i++){
		mut_lock(&mute);
		int j=0;
		while(rand() > RAND_MAX/1000);
		while(j<9){
			printf("%d", j);
			j++;
		}
		printf("\n");
		mut_unlock(&mute);
	}
	return (NULL);
}
/* POUR LES TESTS
int main(int argc, char *argv[]){
	int err;
	
	if(argc != 2) return (EXIT_FAILURE);
	N = atoi(argv[1]); // Nombre de threads

	pthread_t thread[N];
	
	init(mute);
	
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
} */
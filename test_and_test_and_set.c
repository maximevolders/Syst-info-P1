/**************************************
 * test_and_test_and_set.c
 *
 * Programme du verrou test and test and set
 * Dans le cadre du projet 1 du cours LINFO1225 - Systèmes informatiques
 *
 * Gauthier Arnold et Volders Maxime
 **************************************/

//Structure définie dans le fichier test_and_test_and_set.h
#include "test_and_test_and_set.h"

//Variables globales pour faire nos tests

// int N;
// struct mut mute;

/*
 * Initialise la structure, met la variable ver à 0.
 * Argument : Pointeur vers le verrou à initialiser
 * Return : 0 en cas de bon fonctionnement
 * */
int mut_init(struct mut *mu){
	mu->ver=0;
	return 0;
}

/*
 * Echange les valeurs de ver et test
 * Argument : Pointeur vers le verrou
 * Return : test, qui vaut 0 ou 1.
 * */
int mut_testAndSet(struct mut *mu){
	int test=1;
		asm("movl $1, %%eax;"
		"xchgl %%eax, %0;"
		"movl %%eax, %1;"
		:"+m" (mu->ver), "=r" (test) /* paramètres de sortie */
		: /* paramètres d'entrée */
		:"%eax" /* registres modifiés */
		);
	return test;
}

/*
 * Fonction de verrouillage
 * Argument : Pointeur vers la structure mutex à verrouiller
 * */
void mut_lock(struct mut *mu){
	do{
		while(mu->ver == 1);
	} while(mut_testAndSet(mu) == 1);
}

/*
 * Fonction de déverrouillage
 * Argument : Pointeur vers la structure mutex à déverrouiller
 * */
void mut_unlock(struct mut *mu){
	mu->ver = 0;
}
/*
 * Fonction test pour tester nos performances
 * Retirer les commentaires pour pouvoir lancer le code
 * */
/*
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

 */
/* Pour les tests, retirer le commentaire pour lancer le code
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
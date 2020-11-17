#include <stdio.h>
volatile int verrou=0;

/*
void enter(){
	int test=1;
	do{
		int a = test;
		test = verrou;
		verrou = a;
	} while(test == 1);
}
*/

void lock(){
	asm("loop:"
		"movl $1, %%eax;"
		"xchgl %%eax, %0;"
 		"testl %%eax, %%eax;"
		"jne loop;"
		:"=&r"(verrou)
		);
}

void unlock(){
	asm("movl $0, %%eax;"
		"xchgl %%eax, %0;"
		:"=&r"(verrou));
}

int main(int argc, char argv[]){
	printf("Verrou avant lock: %d\n", verrou);
	lock();
	printf("Verrou après lock: %d\n", verrou);
	unlock();
	printf("Verrou après unlock: %d\n", verrou);
	return 0;
}
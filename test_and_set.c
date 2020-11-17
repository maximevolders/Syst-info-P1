#include <stdio.h>
volatile int verrou=0;

void lock(){
	int test=1;
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

int main(int argc, char argv[]){
	printf("Verrou avant lock: %d\n", verrou);
	lock();
	printf("Verrou après lock: %d\n", verrou);
	unlock();
	printf("Verrou après unlock: %d\n", verrou);
	return 0;
}
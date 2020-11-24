typedef struct mut{
	volatile int ver;
}mut;

void mut_init(mut* mu);

int mut_testAndSet(mut* mu);

void mut_lock(mut* mu);

void mut_unlock(mut* mu);
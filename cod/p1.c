#include <pthread.h>
#include <stdio.h>

typedef struct __myarg_t {
	int a;
	int b;
} myarg_t;

void *mythread(void *arg) {
	myarg_t *m = (myarg_t *) arg;
	printf("%d %d\n", m->a, m->b);
	return NULL;
}
pthread_mutex_t trava;

int global  = 0;

void* faz(void *arg){
	int i;
	
	for(int i = 0; i <1000000;i++){
		pthread_mutex_lock(&trava);
		global ++;
		pthread_mutex_unlock(&trava);
	}

}

int main(int argc, char *argv[]) {
	pthread_t p[5];
	int rc , c,x = 0;

	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
	
	

	
	for(int i = 0; i < 5;i++){
	

		rc = pthread_create(&p[i], NULL, faz, NULL);
		
	}
	for(int i = 0; i < 5;i++){
		pthread_join(p[i],NULL);
	}
	printf("final: %d\n",global);
}

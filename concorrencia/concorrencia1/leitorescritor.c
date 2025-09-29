#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include<semaphore.h>

#define MAX 100000


typedef struct _rwlock_t {
   sem_t escrita;
   sem_t lock;
   int leitores;
} rwlock_t;

void rwlock_init(rwlock_t *lock) {
   lock->leitores = 0;
   sem_init(&lock->lock, 0,1); 
   sem_init(&lock->escrita,0, 1); 
}

int nescritas,counter;

rwlock_t lock;

sem_t leitores_chegando;
int leitores_esperando = 0;

void *leitor(void *arg) {
   int local;
   sem_wait(&lock.lock);
   lock.leitores++;
                                                                                                                                                                                                
   if(lock.leitores > 2){
      leitores_esperando++;
      lock.leitores--;
      sem_post(&lock.lock);
      sem_wait(&leitores_chegando); //numero de leitores que tem que rodar 
      sem_wait(&lock.lock);
      lock.leitores++;

   }

   if (lock.leitores == 1)
      sem_wait(&lock.escrita);
   sem_post(&lock.lock);

   
   local = counter; //Leitura

   /*
   oq eu quero fazer?

   eu quero que o numero de leitores para em um determinado NUMERO que "eu" escolher e rode todas as therds
   de leitores que estiver rodando ate finalizar os leitores na quantidade que eu escolhi

   para isso:

   eu preciso saber se o leitor que eu estou é o que eu quer 
   eu preciso que todos os leitores antes que eu escolhi terminem de rodar
   ai ja sabemdo os leitoros terminaram eu preciso "chamar" uma semaforo de escritas para rodar

   mas para isso eu preciso ter cuidado com mtos coisas:
   
   */
   sem_wait(&lock.lock);
   lock.leitores--;
   if (lock.leitores == 0)
      sem_post(&lock.escrita);
      while(leitores_esperando != 0){
         sem_post(&leitores_chegando);
         leitores_esperando--;
      }
   
   sem_post(&lock.lock);
   printf("Leitor %d leu %d\n", ((int)arg),local);
}

void *escritor(void *arg) {
   int i;

   
   for (i = 0; i < nescritas; i++){
      sem_wait(&lock.escrita);
      counter++; //Escrita
      sem_post(&lock.escrita);
      printf("Escreveu %d\n",counter);
      usleep(rand()%100000);
   }
   printf("Escritor Acabou\n");
   return NULL;
}



int main(int argc, char *argv[]) {
   int leitores,i;
   if (argc != 3) {
      fprintf(stderr, "uso: %s leitores nescritas\n",argv[0]);
      exit(1);
   }

   leitores = atoi(argv[1]);
   nescritas = atoi(argv[2]);

   sem_init(&leitores_chegando,0,0);

   rwlock_init(&lock); 
   pthread_t esc, lei[MAX];
   pthread_create(&esc, NULL, escritor, NULL);
   for(i=0;i<leitores;i++){
      pthread_create(&lei[i], NULL, leitor, i);
      usleep(rand()%100000);
   }
   pthread_join(esc, NULL);
   for(i=0;i<leitores;i++){
      pthread_join(lei[i], NULL);
   }
  
   printf("Acabou!\n");
   return 0;
}


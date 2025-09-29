#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

//#include <sched.h> //Descomenta so na questao 4
//#include <unistd.h>

int main(int argc, char** argv){
    /*Descomenta so na questao 4
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    sched_setaffinity(0, sizeof(cpu_set_t), &mask);
    */


    int total_paginas = atoi(argv[1]), iteracoes_totais = atoi(argv[2]);
    int pagesize = 4096; //defina jujur // o meu deu 4096
    int tam = (pagesize * total_paginas) / sizeof(int);
    int salto = pagesize / sizeof(int);
    int* vetor = malloc(sizeof(int) * tam); //vetor de pagesize * total_paginas posicoes
    
    struct timeval inicio,fim;
    gettimeofday(&inicio, NULL);
    for(int i = 0; i < iteracoes_totais; i++){
        for(int j = 0; j < tam; j += salto){
            vetor[j]++;
        }
    }
    gettimeofday(&fim, NULL);
    
    double tempo_total = (fim.tv_sec - inicio.tv_sec) + 
                         (fim.tv_usec - inicio.tv_usec) / 1e6;

    long total_acessos = (long)iteracoes_totais * total_paginas;

    double tempo_medio_por_acesso = tempo_total / total_acessos;

    printf("Tempo total: %.6f segundos\n", tempo_total);
    printf("Tempo médio por iteração: %.20f segundos\n", tempo_medio_por_acesso);

    free(vetor);
}

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

//variáveis globais
int lock1=1,lock2=1; //Permite que as threads sejam liberadas
pthread_mutex_t mutex;
pthread_cond_t cond;


void * thread1 (void *arg)
{
    pthread_mutex_lock(&mutex);
    while(lock1){pthread_cond_wait(&cond, &mutex);} //wait dentro de um looping de execucao
    pthread_mutex_unlock(&mutex);
    printf("Fique a vontade.\n");
    pthread_mutex_lock(&mutex); //evitando condicao de corrida
    lock2++;
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void * thread2 (void *arg)
{
    printf("Seja bem vindo!\n");
    lock1=0;
    pthread_cond_broadcast(&cond);
    pthread_exit(NULL);
}

void * thread3 (void *arg)
{
    while(lock2<3){}
    printf("Volte Sempre!\n");
    pthread_exit(NULL);
}

void * thread4 (void *arg)
{
    pthread_mutex_lock(&mutex);
    while(lock1){pthread_cond_wait(&cond, &mutex);} //wait dentro de um looping de execucao
    pthread_mutex_unlock(&mutex);
    printf("Sente-se por favor.\n");
    pthread_mutex_lock(&mutex); //evitando condicao de corrida
    lock2++;
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main()
{
    int i;
    pthread_t threads[4];
    pthread_cond_init (&cond, NULL); //inicializa variavel de condicao
    pthread_mutex_init(&mutex, NULL); //inicializa
    pthread_create(&threads[0],NULL,thread1,NULL); //Criando das Threads
    pthread_create(&threads[1],NULL,thread2,NULL);
    pthread_create(&threads[2],NULL,thread3,NULL);
    pthread_create(&threads[3],NULL,thread4,NULL);

    for (i=0;i<4;i++) {pthread_join(threads[i], NULL);} //pthread_join
    pthread_mutex_destroy(&mutex);  //desalocando variaveis
    pthread_cond_destroy(&cond);
    pthread_exit(NULL);


}

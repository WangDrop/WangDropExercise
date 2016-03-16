#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#define NBUFF 10
#define MAXTHREAD 1000
int nitems, nproducers, nconsumers;
int fin;
int fout;

struct{
    struct{
        char data[BUFSIZ];
        ssize_t n ;
    }buff[NBUFF];//多个缓冲区
    int nput;
    int nget;
    sem_t mutex, nempty, nstored;
} shared;


void * produce(void *), *consume(void *);

int
main(int argc, char ** argv)
{
    time_t startTime, endTime;
    int i, prodcount[MAXTHREAD], conscount[MAXTHREAD];
    pthread_t tid_produce[MAXTHREAD], tid_consume[MAXTHREAD];
    if(argc != 5){
        perror("Invalid argument!\n");
        exit(0);
    }
    nproducers = atoi(argv[1]);
    nconsumers = atoi(argv[2]);


    fin = open(argv[3], O_RDONLY);
    fout = open(argv[4], O_CREAT | O_RDWR | O_TRUNC);

    sem_init(&shared.mutex, 0, 1);
    sem_init(&shared.nempty, 0, NBUFF);
    sem_init(&shared.nstored, 0, 0);

    //shared.nget = 0;
    //shared.nput = 0;

    pthread_setconcurrency(nproducers + nconsumers);

    time(&startTime);
    for(i = 0; i < nproducers; ++i){
        prodcount[i] = 0;
        pthread_create(&tid_produce[i], NULL, produce, &prodcount[i]);
    }

    for(i = 0; i < nconsumers; ++i){
        conscount[i] = 0;
        pthread_create(&tid_consume[i], NULL, consume, &conscount[i]);
    }

    for(i = 0; i < nproducers; i++){
        pthread_join(tid_produce[i], NULL);
        printf("producer count[%d] = %d\n", i, prodcount[i]);
    }

    for(i = 0; i < nconsumers; i++){
        pthread_join(tid_consume[i], NULL);
        printf("consumer connt[%d] = %d\n", i, conscount[i]);
    }
    close(fin);
    close(fout);

    time(&endTime);
    printf("The total time cost is : %.3f seconds\n", difftime(endTime, startTime));

    sem_destroy(&shared.mutex);
    sem_destroy(&shared.nempty);
    sem_destroy(&shared.nstored);
    exit(0);
}

void * produce(void * arg)
{
    for(;;){
        sem_wait(&shared.nempty);
        sem_wait(&shared.mutex);

        shared.buff[shared.nput%NBUFF].n =
                read(fin, shared.buff[shared.nput%NBUFF].data, BUFSIZ);
        if(shared.buff[shared.nput%NBUFF].n == 0){
            printf("asdasd\n");
            sem_post(&shared.nstored);
            sem_post(&shared.nempty);
            sem_post(&shared.mutex);
            return NULL;
        }
        shared.nput++;

        sem_post(&shared.mutex);
        sem_post(&shared.nstored);
        ++*((int*)arg);
    }
}

void * consume(void * arg)
{
    for(;;){
        sem_wait(&shared.nstored);
        sem_wait(&shared.mutex);

        if(shared.buff[shared.nget%NBUFF].n == 0){
            sem_post(&shared.nstored);
            sem_post(&shared.mutex);
            return (NULL);
        }
        write(fout, shared.buff[shared.nget%NBUFF].data, shared.buff[shared.nget%NBUFF].n);
        if(!(shared.nget%10000))
            printf("Process is going on, please wait...\n");
        shared.buff[shared.nget%NBUFF].n = 0;
        shared.nget++;
        sem_post(&shared.mutex);
        sem_post(&shared.nempty);
        ++*((int*)arg);
    }
}










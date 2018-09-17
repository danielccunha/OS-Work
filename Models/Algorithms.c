#include <pthread.h>
#include "Queue.c"

void *createThread(void *args);

void FIFO_naoPreemptivo(NODE *pN)
{
    pthread_create(&pN->data.info, NULL, createThread, &pN->data.time);
    pthread_join(pN->data.info, NULL);
}

void *createThread(void *args)
{
    int time = *((int *) args);

    printf("Sleeping %d seconds...\n", time);
    sleep(time);
}

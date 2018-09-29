#include <pthread.h>
#include "Queue.c"

struct Data 
{
    int time;
    int priority;
};

void *createThread(void *args);

void runThread(NODE *pN)
{
    struct Data data;
    data.time = pN->data.time;
    data.priority = pN->data.priority;

    pthread_create(&pN->data.info, NULL, createThread, &data);
    pthread_join(pN->data.info, NULL);
}

void *createThread(void *args)
{
    struct Data data = *((struct Data *) args);

    printf("Priority: %d. Sleeping %d seconds...\n", data.priority, data.time);
    sleep(data.time);
}

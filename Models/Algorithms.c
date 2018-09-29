#include <pthread.h>
#include "Queue.c"

struct Data 
{
    int time;
    int priority;
    int initialTime;
};

void *createThread(void *args);

void runThread(NODE *pN)
{
    struct Data data;
    data.time = pN->data.time;
    data.priority = pN->data.priority;
    data.initialTime = pN->data.initialTime;

    pthread_create(&pN->data.info, NULL, createThread, &data);
    pthread_join(pN->data.info, NULL);
}

void *createThread(void *args)
{
    struct Data data = *((struct Data *) args);

    printf("Priority: %d. Initial time: %d. Sleeping %d seconds...\n", data.priority, data.initialTime, data.time);
    sleep(data.time);
}

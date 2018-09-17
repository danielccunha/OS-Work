#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include "Models/Control.c"
#include "Models/Algorithms.c"

#define SLEEPTIME 1

#define NFIFO 1

struct Control ctrl;
Queue* queue;
sem_t semQueue;

void *threadCPU(void *argv);
void *threadGenerator(void *args);
void *threadScheduler(void *args);
void *createThread(void *args);

int main(int argc, char const *argv[])
{
    if (argc < 9)
    {
        printf("Missing parameters\n");
        return -1;
    }

    srand(time(NULL));

    pthread_t tidCPU;
    pthread_create(&tidCPU, NULL, threadCPU, argv);
    pthread_join(tidCPU, NULL);
    
    return 0;
}

void *threadCPU(void *args) 
{
    ctrl = getControl(args);
    queue = ConstructQueue(ctrl.T);

    sem_init(&semQueue, 0, 1);

    pthread_t tidGenerator, tidScheduler;
    pthread_create(&tidGenerator, NULL, threadGenerator, NULL);
    pthread_create(&tidScheduler, NULL, threadScheduler, NULL);
    
    pthread_join(tidGenerator, NULL);
    pthread_join(tidScheduler, NULL);

    DestructQueue(queue);

    return NULL;
}

void *threadGenerator(void *args)
{
    pthread_t tid[ctrl.N];

    for(int i = 0; i < ctrl.N; ++i)
    {
        while (isFull(queue))        
            sleep(SLEEPTIME);

        NODE *pN = (NODE*) malloc(sizeof (NODE));
        pN->data.info = tid[i];
        pN->data.time = ctrl.Min + (rand() % ctrl.Max);
        
        sem_wait(&semQueue);
        Enqueue(queue, pN);
        sem_post(&semQueue);
    }
}

void *threadScheduler(void *args)
{
    int count = 0, total = 0;
    int N = ctrl.N;

    while (count < N)
    {
        while (isEmpty(queue))
            sleep(SLEEPTIME);

        sem_wait(&semQueue);
        NODE *pN = Dequeue(queue);
        sem_post(&semQueue);

        switch (ctrl.A)
        {
            case 1:
                FIFO_naoPreemptivo(pN);
                break;
        }

        total += pN->data.time;
        count++;
    }    

    printf("\nFinished scheduler\n");
    printf("Total time: %d\n", total);
}

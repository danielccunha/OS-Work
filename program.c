#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include "Models/Control.c"
#include "Models/Algorithms.c"

#define SLEEPTIME 1
#define FIFO 1
#define SJF 2
#define NPriority 3

struct Control ctrl;
Queue* queue;
List* list;
sem_t semStruct;
int isQueueAlgorithm = 1;

void *threadCPU(void *argv);
void *threadGenerator(void *args);
void *threadScheduler(void *args);
void *createThread(void *args);
NODE *getFromQueue();
NODE *getFromList();

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
    // TODO Add missing cases
    isQueueAlgorithm = ctrl.A == 1;

    queue = ConstructQueue(ctrl.T);
    list = ConstructList(ctrl.T);

    sem_init(&semStruct, 0, 1);

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
        while ((isQueueAlgorithm && isQueueFull(queue)) || (!isQueueAlgorithm && isListFull(list)))
            sleep(SLEEPTIME);

        NODE *pN = (NODE*) malloc(sizeof (NODE));
        pN->data.info = tid[i];
        pN->data.time = ctrl.Min + (rand() % ctrl.Max);
        pN->data.priority = ctrl.Pi + (rand() % ctrl.Pf);
        pN->key = i;

        sem_wait(&semStruct);
        
        if (isQueueAlgorithm)
            Enqueue(queue, pN);
        else
        {
            insertNode(list, pN);
            sortList(list, ctrl.A);
        }
        
        sem_post(&semStruct);
    }
}

void *threadScheduler(void *args)
{
    int count = 0, total = 0;
    int N = ctrl.N;

    while (count < N)
    {
        while ((isQueueAlgorithm && isQueueEmpty(queue)) || (!isQueueAlgorithm && isListEmpty(list)))
            sleep(SLEEPTIME);

        NODE *pN;        

        switch (ctrl.A)
        {
            case FIFO:
                pN = getFromQueue();
                runThread(pN);
                break;
            
            case SJF: case NPriority:
                pN = getFromList();
                runThread(pN);
                break;
        }

        total += pN->data.time;
        count++;
    }    

    printf("\nFinished scheduler\n");
    printf("Total time: %d\n", total);
}

NODE *getFromQueue()
{
    sem_wait(&semStruct);
    NODE *pN = Dequeue(queue);
    sem_post(&semStruct);

    return pN;
}

NODE *getFromList()
{
    sem_wait(&semStruct);
    NODE *pN = getFirstNode(list);
    sem_post(&semStruct);

    return pN;
}

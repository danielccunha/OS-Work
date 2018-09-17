#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include "Models/Control.c"
#include "Models/Queue.c"

struct Control ctrl;
Queue* queue;

void *threadCPU(void *argv);
void *threadGerador(void *args);
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

    pthread_t tidGerador;
    pthread_create(&tidGerador, NULL, threadGerador, NULL);
    pthread_join(tidGerador, NULL);

    return NULL;
}

void *threadGerador(void *args)
{
    pthread_t tid[ctrl.N];

    for(int i = 0; i < ctrl.N; ++i)
    {
        // TODO: If queue is not full, enqueue another thread
        pthread_create(&tid[i], NULL, createThread, NULL);

        NODE *pN = (NODE*) malloc(sizeof (NODE));
        pN->data.info = tid[i];
        
        Enqueue(queue, pN);
    }
    
    return NULL;
}

void *createThread(void *args)
{
    // TODO: Create thread
    printf("Created thread...\n");
    return NULL;
}

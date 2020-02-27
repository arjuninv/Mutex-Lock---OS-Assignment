
#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 

#define num_readers 5
#define num_writers 5
#define max_workers 20

pthread_t readers[num_readers];
pthread_t writers[num_writers];

pthread_mutex_t lock; 

typedef struct worker {
    int write_val; // Only used of worker is Writer
    int priority; 
    struct worker* next; 
} Worker;

Worker worker_queue[max_workers];
int tail = 0;

void addworker(int priority, int write_val) {
    if (tail == max_workers - 1) {
        // Max workers reached
    } else {
        Worker* new_worker = (Worker*)malloc(sizeof(Worker));
        new_worker->priority = priority; // Readers priority
        if (priority == 2) new_worker->write_val = write_val;
        else new_worker->write_val = -1;
        worker_queue[tail] = *new_worker;
        tail++;
    }
}

Worker *getWorker() {
    int high_priority = -1;
    Worker* high_priority_worker = &worker_queue[0];
    int high_priority_index = 0;
    for (int i = 0; i < tail; i++) {
        Worker* temp_worker = &worker_queue[i];
        if (temp_worker->priority <= high_priority) {
            high_priority_worker = temp_worker;
            high_priority_index = i;
        }
    }

    for (int i = high_priority_index; i<tail-1; i++) {
        worker_queue[i] = worker_queue[i+1];
    }
    tail--;
    return high_priority_worker;
}


int theSharedGlobalVar = 0;


int main(void) 
{
     
    pthread_join(tid[0], NULL); 
    pthread_join(tid[1], NULL); 

  
    return 0; 
} 

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h>
#include <time.h> 

#define max_workers 5

pthread_mutex_t lock; 
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER; 

int shared_variable = 0;

int writer_queue[max_workers];
int writer_count = 0;

int reader_count = 0;

void *read_func(void *args) {
    pthread_mutex_lock(&lock);
    
    sleep(rand() % 5);

    printf("The value read %d\n", shared_variable);
    reader_count--;
    printf("The number of readers present when value is read %d\n", reader_count);
    if (reader_count == 0) {
        pthread_cond_broadcast(&cond1); 
    }

    pthread_mutex_unlock(&lock); 
}

void *write_func(void *args) {
    pthread_mutex_lock(&lock);
    pthread_cond_wait(&cond1, &lock); 

    sleep(rand() % 5);

    shared_variable = writer_queue[writer_count-1];

    printf("The written value %d\n", writer_queue[writer_count-1]);
    printf("The number of readers present were when value is written %d\n", reader_count);

    writer_count--;
    pthread_mutex_unlock(&lock); 
}

int main(void) 
{
    srand(time(0)); 
    printf("Enter number of readers: ");
    scanf("%d", &reader_count);

    printf("Enter number of writers: ");
    scanf("%d", &writer_count);

    if(writer_count > max_workers) {
        printf("Writer count out of bound (%d)", max_workers);
        return -1;
    }

    printf("Enter (%d) values for writers to write: ", writer_count);
    for (int i=0; i<writer_count; i++) {
        scanf("%d", &writer_queue[i]);
    }

    
    int reader_left = reader_count;
    int writer_left = writer_count;
    int READER_COUNT = reader_count;
    int WRITER_COUNT = writer_count;

    pthread_t reader_thread_id[reader_count];
    pthread_t writer_thread_id[writer_count];

    // Random initialization of readers & writers
    while (reader_left > 0 || writer_left > 0) {
        if (rand() % 2 && reader_left > 0) {
            pthread_create(&reader_thread_id[reader_left-1], NULL, read_func, NULL);
            reader_left--;
        } else if (writer_left > 0) {
            pthread_create(&writer_thread_id[writer_left-1], NULL, write_func, NULL);
            writer_left--;
        }
    }

    if (READER_COUNT == 0) {
        pthread_cond_broadcast(&cond1);
    }
    // Wait for all threads to be executed
    for (int i=0; i<WRITER_COUNT; i++) {
        pthread_join(writer_thread_id[i], NULL); 
    }

    for (int i=0; i<READER_COUNT; i++) {
        pthread_join(reader_thread_id[i], NULL); 
    }


  
    return 0; 
} 
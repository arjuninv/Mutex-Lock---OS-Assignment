
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h>
#include <time.h> 

#define max_writers 20

pthread_mutex_t lock; 

int shared_variable = 0;

int writer_queue[max_writers];
int writer_count = 0;

int reader_count = 0;

void *read_func(void *args) {
    pthread_mutex_lock(&lock);
    
    sleep(rand() % 5);

    printf("The value read %d\n", shared_variable);
    reader_count--;
    printf("The number of readers present when value is read %d\n", reader_count);


    pthread_mutex_unlock(&lock); 
}

void *write_func(void *args) {
    while (reader_count != 0);
    pthread_mutex_lock(&lock);

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

    printf("Enter (%d) values for writers to write: ", writer_count);
    for (int i=0; i<writer_count; i++) {
        scanf("%d", &writer_queue[i]);
    }

    
    int reader_left = reader_count;
    int writer_left = writer_count;

    pthread_t reader_thread_id[reader_count];
    pthread_t writer_thread_id[writer_count];

    // Random initialization of readers & writers

    for (int i=0; i<writer_count; i++) {
        pthread_create(&reader_thread_id[reader_left-1], NULL, read_func, NULL);    
    }

    for (int i=0; i<reader_count; i++) {
        pthread_create(&writer_thread_id[writer_left-1], NULL, write_func, NULL);
    }

    // Wait for all threads to be executed
    for (int i=0; i<writer_count; i++) {
        pthread_join(writer_thread_id[i], NULL); 
    }

    for (int i=0; i<reader_count; i++) {
        pthread_join(reader_thread_id[i], NULL); 
    }


  
    return 0; 
} 
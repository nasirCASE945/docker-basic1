#include <stdio.h>

#include <pthread.h>

// size of array 
#define MAX 16 
 
// maximum number of threads 

#define NUM_THREADS 4

int a[] = { 1, 5, 7, 10, 12, 14, 15, 18, 20, 22, 25, 27, 30, 64, 110, 220 }; 
    int sum[MAX] = { 0 }; 
    int part = 0;

void *thread_function(void *arg) {
    int thread_id = *(int *)arg;
   
    
     int thread_part = part++; 
 
    for (int i = thread_part * (MAX / 4); i < (thread_part + 1) * (MAX / 4); i++) 
        sum[thread_part] += a[i]; 

    printf("Thread %d computed sum of part %d: %d\n", thread_id, thread_part, sum[thread_part]);

    
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];


    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }
  int total_sum = 0; 
    for (int i = 0; i < NUM_THREADS; i++) 
        total_sum += sum[i]; 

 
    printf("in main Total sum: %d\n", total_sum);

    return 0;
}
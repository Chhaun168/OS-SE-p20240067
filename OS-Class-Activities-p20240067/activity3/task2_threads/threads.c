#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4

int shared_counter = 0;

void *worker(void *arg) {
    int id = *(int *)arg;

    printf("Thread %d starting...\n", id);

    for (int i = 0; i < 100000; i++) {
        shared_counter++;   // ❌ race condition
    }

    printf("Thread %d done.\n", id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, worker, &ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Expected: %d\n", NUM_THREADS * 100000);
    printf("Actual: %d\n", shared_counter);

    return 0;
}

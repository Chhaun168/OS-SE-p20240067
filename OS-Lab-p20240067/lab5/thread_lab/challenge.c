#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t keep_running = 1;

void signal_handler(int sig) {
    printf("\nSIGINT received. Stopping threads...\n");
    keep_running = 0;
}

void* worker(void* arg) {

    long id = (long)arg;

    while (keep_running) {
        printf("Worker thread %ld is running...\n", id);
        sleep(1);
    }

    printf("Worker thread %ld exiting...\n", id);

    pthread_exit(NULL);
}

int main() {

    pthread_t t1, t2;

    signal(SIGINT, signal_handler);

    pthread_create(&t1, NULL, worker, (void*)1);
    pthread_create(&t2, NULL, worker, (void*)2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("All threads cleanly exited. Goodbye.\n");

    return 0;
}

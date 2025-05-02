#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

#define NUM_THREADS 4
pthread_t threads[NUM_THREADS];

void thread_sig_handler(int signum) {
    printf("Thread %lu received signal in custom handler\n", pthread_self());
    pthread_exit(NULL);  // Add this to exit the thread after handling
}

void* thread_function(void* arg) {
    struct sigaction sa;
    sa.sa_handler = thread_sig_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    
    // Each thread sets its own handler
    sigaction(SIGUSR1, &sa, NULL);
    
    printf("Thread %lu waiting for signal...\n", pthread_self());
    pause();  // Changed from while(1) pause() to just pause()
    return NULL;
}

int main() {
    // Main thread uses default handler
    signal(SIGUSR1, SIG_DFL);
    
    // Create threads
    for(int i = 0; i < NUM_THREADS; i++) {
        if(pthread_create(&threads[i], NULL, thread_function, NULL) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }
    
    sleep(1); // Let threads initialize
    printf("Main thread %lu sending signals...\n", pthread_self());
    
    // Send signal to each thread individually
    for(int i = 0; i < NUM_THREADS; i++) {
        printf("Sending to thread %d...\n", i);
        pthread_kill(threads[i], SIGUSR1);
        usleep(100000);  // Small delay between signals for cleaner output
    }
    
    // Wait for threads
    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("All threads completed successfully!\n");
    return 0;
}
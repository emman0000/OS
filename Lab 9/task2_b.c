#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

#define NUM_THREADS 4
pthread_t threads[NUM_THREADS];

// Get thread ID (Linux specific)
pid_t gettid() {
    return syscall(SYS_gettid);
}

// Signal handler that exits the thread
void sigusr1_handler(int signum) {
    printf("Thread %lu (TID: %d) received SIGUSR1\n", 
           pthread_self(), gettid());
    pthread_exit(NULL);
}

// Thread function with proper signal handling
void* thread_function(void* arg) {
    // Block SIGUSR1 in all threads initially
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    pthread_sigmask(SIG_BLOCK, &mask, NULL);
    
    printf("Thread %lu (TID: %d) waiting for signal...\n",
           pthread_self(), gettid());
    
    // Wait for signal
    int sig;
    sigwait(&mask, &sig);
    
    printf("Thread %lu (TID: %d) processing signal...\n",
           pthread_self(), gettid());
    return NULL;
}

int main() {
    printf("Main thread ID: %lu\n", pthread_self());
    
    // Create threads
    for(int i = 0; i < NUM_THREADS; i++) {
        if(pthread_create(&threads[i], NULL, thread_function, NULL) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }
    
    sleep(1); // Let threads initialize
    
    // Send signal to specific threads
    printf("\nSending signals:\n");
    printf("1. Sending to thread 0...\n");
    pthread_kill(threads[0], SIGUSR1);
    
    printf("2. Sending to thread 2...\n");
    pthread_kill(threads[2], SIGUSR1);
    
    printf("3. Sending to entire process...\n");
    kill(getpid(), SIGUSR1);
    
    // Wait for threads
    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("\nAll threads completed successfully!\n");
    return 0;
}
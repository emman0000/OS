                  #include <stdio.h>
                  #include <stdlib.h>
                  #include <pthread.h>
                  #include <signal.h>
                  #include <unistd.h>
                  #include <sys/types.h>
                  #include <sys/syscall.h>
                  
                  #define NUM_THREADS 4
                  pthread_t threads[NUM_THREADS]; // Global variable to store thread IDs
                  
                  // Helper function to get thread ID (since gettid() is Linux-specific)
                  pid_t gettid() {
                      return syscall(SYS_gettid);
                  }
                  
                  void sigusr1_handler(int signum) { // signal handler
                      pid_t i = gettid();
                      pid_t j = getpid();
                      fprintf(stdout,"Thread %u received SIGUSR1 signal (parent=%u) [pid=%u] (tid=%u)\n", 
                             (unsigned int)pthread_self(), (unsigned int)j, (unsigned int)j, (unsigned int)i);
                  }
                  
                  void *thread_function(void *arg) { // thread function
                      signal(SIGUSR1, sigusr1_handler); // register signal handler
                      while (1) sleep(1); // Keep the thread alive
                      return NULL;
                  }
                  
                  int main() {
                      signal(SIGUSR1, sigusr1_handler); // register signal handler
                      
                      for (int i = 0; i < NUM_THREADS; ++i) {
                          if (pthread_create(&threads[i], NULL, thread_function, NULL) != 0) {
                              perror("pthread_create"); 
                              exit(EXIT_FAILURE);
                          }
                      }
                      
                      pid_t i = gettid();
                      pid_t j = getpid();
                      fprintf(stdout,"Parent Process ID: %u, Process ID:%u, main() thread ID: %u\n",
                             (unsigned int)j, (unsigned int)j, (unsigned int)i);
                      fprintf(stdout,"Thread IDs: 0=%u, 1=%u, 2=%u and 3=%u\n",
                             (unsigned int)threads[0], (unsigned int)threads[1], 
                             (unsigned int)threads[2], (unsigned int)threads[3]);
                      
                      // Send signals
                      kill(j, SIGUSR1); // send signal to process
                      pthread_kill(threads[2], SIGUSR1); // send signal to 3rd thread
                  
                      for (int i = 0; i < NUM_THREADS; ++i) {
                          if (pthread_join(threads[i], NULL) != 0) {
                              perror("pthread_join"); 
                              exit(EXIT_FAILURE);
                          }
                      }
                      return 0;
                  }
  ![image](https://github.com/user-attachments/assets/5bfd9351-86d1-42e0-aedd-1c17f718798a)

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
  ![image](https://github.com/user-attachments/assets/6243d7d2-d296-4648-86f3-3a72cf801a6b)
  
      

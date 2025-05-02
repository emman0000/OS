    
    
    #include <stdio.h>
    #include <signal.h>
    #include <sys/wait.h>
                  #include <sys/resource.h>
                  #include <stdlib.h>  // Added for exit() and rand()
                  #include <unistd.h>  // Added for fork(), pause()
                  
                  void proc_exit() {
                      int wstat;
                      pid_t pid;
                  
                      while(1) {
                          // Get info about child process
                          // WNOHANG returns immediately if there is no child to wait
                          pid = wait3(&wstat, WNOHANG, NULL);
                          if(pid == 0 || pid == -1) {
                              fprintf(stdout, "return value of wait3() is %d\n", pid);
                              return;
                          }
                          fprintf(stdout, "Return code: %d\n", wstat);
                      }
                  }
                  
                  int main() {
                      signal(SIGCHLD, proc_exit);
                      switch(fork()) {
                          case -1:
                              perror("main: fork");
                              exit(0);
                          case 0:
                              printf("I'm alive (temporarily)\n"); // child only executes this and exits
                              int ret_code = rand();
                              printf("Return code is %d\n", ret_code);
                              exit(ret_code);  // Added missing semicolon
                          default:
                              pause(); // Fixed: removed erroneous | character
                      }
                      exit(0);
                  }
    
  ![image](https://github.com/user-attachments/assets/5406eb4e-65fa-408b-bc9f-c813c8eea281)

  
  
  
  
          #include <stdio.h>
        #include <signal.h>
        #include <sys/wait.h>
        #include <sys/resource.h>
        #include <stdlib.h>
        #include <unistd.h>
        
        void proc_exit() {
            int wstat;
            pid_t pid;
        
            while(1) {
                pid = wait3(&wstat, WNOHANG, NULL);
                if(pid == 0 || pid == -1) {
                    fprintf(stdout, "return value of wait3() is %d\n", pid);
                    return;
                }
                fprintf(stdout, "Child %d exited with status: %d\n", pid, WEXITSTATUS(wstat));
            }
        }
        
        int main() {
            signal(SIGCHLD, proc_exit);
            
            for(int i = 0; i < 3; i++) {
                pid_t pid = fork();
                if(pid == -1) {
                    perror("fork");
                    exit(1);
                }
                else if(pid == 0) { // Child process
                    printf("Child %d (PID: %d) started\n", i+1, getpid());
                    sleep(1); // Let children live briefly
                    int ret_code = rand() % 100;
                    printf("Child %d exiting with code %d\n", i+1, ret_code);
                    exit(ret_code);
                }
                // Parent continues looping
            }
            
            printf("Parent (PID: %d) sleeping for 10 seconds...\n", getpid());
            sleep(10); // Give time to check for zombies
            
            printf("Parent exiting\n");
            return 0;
        }
          
          
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  ![image](https://github.com/user-attachments/assets/d38d5e61-479b-4ea9-a688-3d30feb3c01a)


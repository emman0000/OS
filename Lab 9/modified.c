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
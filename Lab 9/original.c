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
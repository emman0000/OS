#include <iostream>
#include <unistd.h>   
#include <sys/wait.h> 

using namespace std;

int main() {
    pid_t pid = fork();

    if (pid < 0) {  
        cerr << "Fork failed!" << endl;
        return 1;
    }
    else if (pid == 0) {  
        cout << "Child process executing 'ls -l':\n" << endl;
        execlp("ls", "ls", "-l", NULL);

        cerr << "execlp failed!" << endl;
        return 1;
    }
    else {  
        wait(NULL);  
        cout << "Parent process: Child has finished execution." << endl;
    }

    return 0;
}


#include <iostream>
#include <unistd.h> 
#include <sys/wait.h> 

using namespace std;

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        cout << "Fork Failed!" << endl;
        return 1;
    } 
    else if (pid == 0) {
        for (int i = 0; i < 100; i++) {
            cout << "I AM A CHILD PROCESS" << endl;
        }
    } 
    else {
        for (int i = 0; i < 100; i++) {
            cout << "I AM A PARENT PROCESS" << endl;
        }
        wait(NULL);
    }
    
    return 0;
}


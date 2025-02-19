#include <iostream>
#include <unistd.h>  
#include <signal.h>  
using namespace std;


void handle_alarm(int signum) {
    cout << "\nAlarm received! Program terminating gracefully.\n";
    exit(0);  
}

int main() {
   
    signal(SIGALRM, handle_alarm);

 
    alarm(5);
    cout << "Alarm set for 5 seconds. Program will print messages every second...\n";

    int count = 1;
    while (true) {
        cout << "Message " << count++ << ": Running..." << endl;
        sleep(1); 
    }

    return 0;
}


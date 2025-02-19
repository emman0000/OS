#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
using namespace std;

int main(){
pid_t pid1, pid2;
pid1 = fork();

if (pid1 == 0){cout<<"Child 1 PID : "<<getpid()<<endl;}
else{ pid2 = fork(); if (pid2 == 0){ cout<<"Child 2 PID : "<<getpid()<<endl;}
else{ wait(NULL); wait(NULL); cout<<"Both Children have been terminated. Terminated...\n";}}
return 0;
}
